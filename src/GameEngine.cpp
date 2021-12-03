#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
#include <cmath>
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include <exception>
#include "CommandProcessor.h"
#include "PlayerStrategies.h"

namespace fs = filesystem;
using namespace std;

/* ***************************** */
/*        Custom debugger        */
/* ***************************** */
bool debuggingMode = true; // Setting the value to true will run the program with debug messages

section debugsection = section::all;

// Noah: debugger that only prints debugging message when debugging mode is true
void dprint(string message, section option)
{
    if (debuggingMode)
    {
        if (section::all == debugsection)
        {
            std::cout << message << std::endl;
            return void();
        }
        else
        {
            if (option == debugsection)
            {
                std::cout << message << std::endl;
                return void();
            }
        }
    }
}

// debugger which stops execution of code at inserted point
void pressToContinueWith(string msg)
{
    string x;
    cout << "Press any key to continue..." << msg << endl;
    cin >> x;
}

/* ************************************************************************** */
/*              State, Transition, GameEngine basic functions                 */
/* ************************************************************************** */

State::State()
{
    nameState = "";
}

State::State(string name)
{
    nameState = name;
}

State::State(string name, vector<Transition *> t)
{
    nameState = name;
    transitions = t;
}

State::State(const State &s)
{
    nameState = s.nameState;
    transitions = vector<Transition *>(
        s.transitions); // Using vector copy constructor! Works, demonstration in testGameEngine
}

State::~State()
{
    // for (auto t : transitions) { delete t; }
    transitions.clear();
}

State &State::operator=(const State &c)
{
    if (this == &c)
        return *this;
    this->nameState = c.nameState;
    this->transitions = c.transitions; // Using the vector assignment operator
    return *this;
}

void State::addTransition(Transition *t)
{
    transitions.push_back(t);
}

Transition::Transition()
{
    nameTransition = "";
    nextState = new State();
}

Transition::Transition(string name)
{
    nameTransition = name;
    nextState = new State();
}

Transition::Transition(string name, State *s)
{
    nameTransition = name;
    nextState = s;
}

Transition::Transition(const Transition &t)
{
    nameTransition = t.nameTransition;
    nextState = new State(*(t.nextState));
}

Transition::~Transition()
{
    delete nextState;
}

Transition &Transition::operator=(const Transition &t)
{
    if (this == &t)
        return *this;
    this->nameTransition = t.nameTransition;
    if (nextState)
    {
        delete nextState;
    }
    this->nextState = new State(*(t.nextState));
    return *this;
}

// using default value
GameEngine::GameEngine(std::string newFile)
{
    // Create the states and add to states collection
    initStates();

    // Initialization
    currentPlayers = vector<Player *>();
    initializedRand(); // randomize deck
    deck = new Deck(30);
    map = new Map();
    validTransition = false;
    if (newFile.empty())
    {
        commandProcessor = new CommandProcessor();
    }
    else
    {
        commandProcessor = new FileCommandProcessorAdapter(newFile);
    }

    /* New additions */
    vector<Player *> eliminatedPlayers = vector<Player *>();
    // we cannot delete players or remove them from currentPlayers
    // we can only delete them at the end of a game, when gameengine destructor is called
}

void GameEngine::initStates()
{
    State *startState = new State("start");
    State *tournamentState = new State("tournament");
    State *maploadedState = new State("maploaded");
    State *mapvalidatedState = new State("mapvalidated");
    State *playersaddedState = new State("playersadded");
    State *assignreinforcementState = new State("assignreinforcement");
    State *issueordersState = new State("issueorder");
    State *executeordersState = new State("executeorders");
    State *winState = new State("win");
    State *finalState = new State("final");

    // Adding all states in the collection of the GameEngine
    states = vector<State *>();
    states.push_back(startState);
    states.push_back(tournamentState);
    states.push_back(maploadedState);
    states.push_back(mapvalidatedState);
    states.push_back(playersaddedState);
    states.push_back(assignreinforcementState);
    states.push_back(issueordersState);
    states.push_back(executeordersState);
    states.push_back(winState);
    states.push_back(finalState);

    // Setting current state to the start state
    currentState = startState;

    // Create the transitions
    Transition *tournamentTransition = new Transition("tournament", tournamentState);
    Transition *loadmapTransition = new Transition("loadmap", maploadedState);
    Transition *validatemapTransition = new Transition("validatemap", mapvalidatedState);
    Transition *addplayerTransition = new Transition("addplayer", playersaddedState);
    Transition *gamestart = new Transition("gamestart", assignreinforcementState);
    Transition *issueorderTransition = new Transition("issueorder", issueordersState);
    Transition *endissueordersTransition = new Transition("endissueorders", executeordersState);
    Transition *execorderTransition = new Transition("execorder", executeordersState);
    Transition *endexecordersTransition = new Transition("endexecorders", assignreinforcementState);
    Transition *winTransition = new Transition("win", winState);
    Transition *playTransition = new Transition("replay", startState);
    Transition *endTransition = new Transition("quit", finalState);

    // Add transition to collection of transitions
    transitions = vector<Transition *>();
    transitions.push_back(tournamentTransition);
    transitions.push_back(loadmapTransition);
    transitions.push_back(validatemapTransition);
    transitions.push_back(addplayerTransition);
    transitions.push_back(gamestart);
    transitions.push_back(issueorderTransition);
    transitions.push_back(endissueordersTransition);
    transitions.push_back(execorderTransition);
    transitions.push_back(endexecordersTransition);
    transitions.push_back(winTransition);
    transitions.push_back(playTransition);
    transitions.push_back(endTransition);

    // Add transitions to the states
    startState->addTransition(loadmapTransition);
    startState->addTransition(tournamentTransition);
    maploadedState->addTransition(loadmapTransition);
    maploadedState->addTransition(validatemapTransition);
    mapvalidatedState->addTransition(addplayerTransition);
    playersaddedState->addTransition(addplayerTransition);
    playersaddedState->addTransition(gamestart);
    assignreinforcementState->addTransition(issueorderTransition);
    issueordersState->addTransition(issueorderTransition);
    issueordersState->addTransition(endissueordersTransition);
    executeordersState->addTransition(execorderTransition);
    executeordersState->addTransition(endexecordersTransition);
    executeordersState->addTransition(winTransition);
    winState->addTransition(playTransition);
    winState->addTransition(endTransition);
}

GameEngine::GameEngine(const GameEngine &e)
{
    numberOfPlayers = e.numberOfPlayers;
    currentState = new State(*e.currentState);
    validTransition = e.validTransition;
    states = vector<State *>(e.states);
    transitions = vector<Transition *>(e.transitions);
    commandProcessor = new CommandProcessor(*e.commandProcessor);
    listOfFile = vector<string>(e.listOfFile);
    currentPlayers = vector<Player *>(e.currentPlayers);
    vector<Player *> eliminatedPlayers = vector<Player *>(e.eliminatedPlayers);
    map = new Map(*e.map);
}

/* TODO */
// Destructor gives malloc error
GameEngine::~GameEngine()
{
    // deallocate states and transitions
    for (auto state : states)
    {
        delete state;
    }
    states.clear();
    for (auto transition : transitions)
    {
        delete transition;
    }
    transitions.clear();

    // deallocate other vectors
    for (auto p : currentPlayers)
    {
        delete p;
    }
    currentPlayers.clear();
    for (auto p : eliminatedPlayers)
    {
        delete p;
    }
    eliminatedPlayers.clear();
    delete deck;
    delete commandProcessor;
    delete map;
}

GameEngine &GameEngine::operator=(const GameEngine &e)
{
    if (this == &e)
        return *this;

    if (currentState)
    {
        delete currentState;
    }
    currentState = new State(*e.currentState);
    if (commandProcessor)
    {
        delete commandProcessor;
    }
    commandProcessor = new CommandProcessor(*e.commandProcessor);

    for (vector<State *>::iterator it = states.begin(); it != states.end(); ++it)
    {
        State *a = *it;
        delete a;
        a = NULL;
    }
    states.clear();
    states = vector<State *>(e.states);

    for (vector<Transition *>::iterator it = transitions.begin(); it != transitions.end(); ++it)
    {
        Transition *a = *it;
        delete a;
        a = NULL;
    }
    transitions.clear();
    transitions = vector<Transition *>(e.transitions);
    for (vector<Player *>::iterator it = currentPlayers.begin(); it != currentPlayers.end(); ++it)
    {
        Player *a = *it;
        delete a;
        a = NULL;
    }
    currentPlayers.clear();
    currentPlayers = vector<Player *>(e.currentPlayers);

    return *this;
}

string GameEngine::getCurrentStateName()
{
    return currentState->nameState;
}

vector<string> GameEngine::getNextTransitions()
{
    vector<string> transitionsNames;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        transitionsNames.push_back(currentState->transitions.at(i)->nameTransition);
    }
    return transitionsNames;
}

string GameEngine::getNextStateName(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            return currentState->transitions.at(i)->nextState->nameState;
        }
    }
    return ""; // TODO: throw exception
}

// Makes the engine transitions to the next state if command is valid.
// Returns boolean to help debugging or more validation
bool GameEngine::doTransition(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            currentState = currentState->transitions.at(i)->nextState;
            validTransition = true;
            notify(this);
            return true;
        }
    }
    validTransition = false;
    return false;
}

string GameEngine::stringToLog()
{
    return "GameEngine transitioned to a new state: " + currentState->nameState;
}

/* ****************************************************************** */
/*                    GameEngine Helper Functions                     */
/* ****************************************************************** */

Map *GameEngine::getMap()
{
    return map;
}

int GameEngine::getNumOfPlayers()
{
    return numberOfPlayers;
}

void GameEngine::setNumOfPlayers(int plNumb)
{
    numberOfPlayers = plNumb;
}

void GameEngine::randomizePlayersTurn()
{ // for randomizing players order of appearance on gamestart
    shuffle(begin(currentPlayers), end(currentPlayers), default_random_engine{});
    cout << "players shuffled...\n"
         << endl;
}

vector<Player *> &GameEngine::getPlayers()
{
    return currentPlayers;
}

vector<Player *> &GameEngine::getEliminatedPlayers()
{
    return eliminatedPlayers;
}

void GameEngine::addOneEliminatedPlayer(Player *p)
{
    eliminatedPlayers.push_back(p);
}

void GameEngine::getMapList()
{ // helper method for loading list of maps from the directory in an ordered list
    int i = 0;
    string path = "../maps/";
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.path().extension() == ".map")
        {
            std::cout << i + 1 << ": " << entry.path().filename() << endl;
            listOfFile.push_back(entry.path().filename().string());
            i++;
        }
    }
}

void GameEngine::setMap(Map *m)
{
    map = m;
}

Deck *GameEngine::getDeck()
{
    return deck;
}

/* ****************************************************************** */
/*                  Command Processor Driver for A2                   */
/* ****************************************************************** */
// A2 Part 1: Command Processor
void GameEngine::testGameEngine()
{
    Command *output;
    cout << "Welcome to WarZone!" << endl;
    while (true)
    {
        // To handle replay case, getCommand has to be called at a later execution
        output = commandProcessor->getCommand(currentState);
        doTransition(output->getCommandName());
        if (output->getCommandName() == "gamestart")
        {
            // Start the gameloop
            break;
        }
        else if (output->getCommandName() == "replay")
        {
            // Call me later
            cout << "\n";
        }
        else if (output->getCommandName() == "quit")
            exit(0);
        cout << "\n";
    }
    cout << "\n";
    cout << "Voila tous les commands: " << endl;
    commandProcessor->printCommands();
}

/* **************************************************************************** */
/*                  Startup Phase Driver and helper functions                   */
/* **************************************************************************** */

// Two main phases
void GameEngine::preStartup()
{
    Command *command;

    do
    {
        command = commandProcessor->getCommand(currentState);
    } while (command->getArgs().empty() || !doTransition(command->getCommandName()));

    if (currentState->nameState == "tournament")
    {
        enterTournamentMode(command);
    }

    // starting with loadmap
    string path = "../maps/";
    MapLoader *mapLoader = new MapLoader();
    cout << "Initiating map loading stage: \n"
         << endl;
    getMapList();

    string mapName = command->getArgs()[0];
    cout << "current command: " << command->getCommandName() << "\n"
         << endl;
    cout << "current mapfile requested: " << mapName << "\n"
         << endl;

    string fpath = path.append(mapName);
    Map x1 = *mapLoader->loadMap(fpath);
    Map *map1 = new Map(x1);
    cout << "Map " << mapName << " has been loaded. \n"
         << endl;

    do
    {
        command = commandProcessor->getCommand(currentState);
    } while (!doTransition(command->getCommandName()));

    map1->validate(); // validates map
    map1->showLoadedMap();
    setMap(map1);

    // addplayer loop
    while (true)
    {
        do
        {
            command = commandProcessor->getCommand(currentState);
        } while (command->getArgs().empty() || !doTransition(command->getCommandName()));
        string cmdPlName = command->getArgs()[0];

        numberOfPlayers++;
        setNumOfPlayers(numberOfPlayers);
        Player *p = new Player();
        p->setPlName(cmdPlName);
        p->setReinforcementPool(5);
        cout << *p << "Number of Armies: " << p->getReinforcementPool() << endl;
        cout << "Cards in players hand: " << p->getHand() << endl; // TODO: prints address
        currentPlayers.push_back(p);

        cout << "total number of players so far is: " << getNumOfPlayers() << endl;
        if (getNumOfPlayers() == 1)
        {
            cout << "have 1 player so far" << endl;
            continue;
        }
        if (getNumOfPlayers() < 7 && commandProcessor->fileName.empty())
        {
            cout << "continue adding players? (y/n)" << endl;
            string keyInY;
            getline(cin, keyInY);
            if (keyInY == "y")
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    do
    {
        command = commandProcessor->getCommand(currentState);
    } while (!doTransition(command->getCommandName()));

    StartupPhase sp;
    sp.setGameEng(this);
    sp.startup();
}

// startupPhase methods
StartupPhase::StartupPhase()
{
    eng = new GameEngine();
}

StartupPhase::StartupPhase(const StartupPhase &sp)
{
    this->eng = sp.eng;
}

StartupPhase::~StartupPhase()
{
    // TODO: missing destructor
    // delete eng;
}

void StartupPhase::operator=(const StartupPhase &sp)
{
    eng = sp.eng;
}

ostream &operator<<(ostream &out, const StartupPhase &sp)
{
    // out<<"\nGame Engine: "<<sp.eng<< endl;//TODO: fix
    return out;
}

std::istream &operator>>(std::istream &in, const StartupPhase &sp)
{
    // in>>sp.eng; //TODO: fix
    return in;
}

void StartupPhase::setGameEng(GameEngine *en)
{
    eng = en;
}

void StartupPhase::startup()
{
    // randomizing players order
    vector<Player *> &players = eng->getPlayers();
    cout << "Randomize player order: \n"
         << endl;
    eng->randomizePlayersTurn();
    cout << "Current order of players after randomize: \n"
         << endl;
    for (Player *p : players)
    {
        cout << *p << "----" << endl;
    }

    // giving armies to players:
    cout << "Starting Army distribution for players: \n"
         << endl;
    for (int i = 0; i < eng->getNumOfPlayers(); i++)
    {
        players[i]->setReinforcementPool(5);
    }
    cout << "Players have received 50 army each! \n"
         << endl;
    for (Player *p : players)
    {
        cout << "player " << p->getName() << ": " << p->getReinforcementPool() << endl;
    }

    // letting players draw 2 cards
    for (Player *p : players)
    {
        Hand *h = new Hand();
        p->setCards(h);
        Deck *deck = eng->getDeck();
        for (int i = 0; i <= 2; i++)
        {
            deck->draw(*p);
        }
        cout << p->getName() << " drew 2 cards!" << endl;
    }

    // territory assignment
    cout << "Distributing territories to the players: \n"
         << endl;
    Map *map = eng->getMap();
    if (!map->territoryNodeList.empty())
    {
        shuffle(begin(map->territoryNodeList), end(map->territoryNodeList), default_random_engine());

        while (!map->territoryNodeList.empty())
        {
            vector<Player *> &players = eng->getPlayers();
            for (Player *p : players)
            {
                if (!map->territoryNodeList.empty())
                {
                    vector<Territory *> territories;
                    territories.push_back(map->territoryNodeList.back());
                    p->addTerritories(territories);
                    map->territoryNodeList.pop_back();
                    for (Territory *t : territories)
                    { // Bug: only one territory is assigned to each player...
                        t->setOwner(p);
                    }
                }
            }
        }
        // for displaying players with acquired territories
        for (Player *p : eng->getPlayers()) // getPlayers() returns a vector&
        {
            cout << *p << endl;
        }

        dprint("= Debugging before gamestart: Hardcoding player strategies\n", section::startup);
        // Hardcode first 2 players' strategies
        eng->getPlayers().at(0)->setPlayerStrategy(new CheaterPlayerStrategy(eng->getPlayers().at(0)));
        for (auto player : eng->getPlayers())
        {
            dprint("\t" + player->getName() + " uses strat " + player->getPlayerStrategy()->strategyName(), section::startup);
        }
    }
    else
    {
        cout << "The map has loading problems" << endl;
    }
}

/* ********************************************************************** */
/*                  Helper functions for Main Game Loop                   */
/* ********************************************************************** */

void GameEngine::auditPlayers()
{
    for (Player *p : currentPlayers)
    {
        if (p->getTerritories().size() == 0)
        {
            string msg = "GameEngine::auditPlayer found a losing player: \nPlayer " + p->getName() + " no longer has any territories left and will be removed from the game \n";
            dprint(msg, section::all);

            currentPlayers.erase(remove(currentPlayers.begin(), currentPlayers.end(), p));

            // add to eliminated players vector
            addOneEliminatedPlayer(p);
        }
    }
}

Player *GameEngine::hasWinner()
{
    // Get the players territories
    for (Player *p : currentPlayers)
    {

        if (map->getTerritorySize() == p->getTerritories().size())
        {
            return p;
        }
    }

    return NULL;
}

void GameEngine::reinforcementPhase(Player *p)
{
    // ! Leave the debugging messages "reached here ..." This phase is susceptible to segmentation faults.

    /* ******************* */
    /*      Card Bonus     */
    /* ******************* */

    // Check if player won territories in the last round. If yes, draw one card max
    int numConqueredTerritories = p->getTerritorySize() - p->getPrevTerritorySize();
    if (numConqueredTerritories > 0)
        // deck->draw(*p); // Segmentation fault: to investigate

        // update prevTerritorySize
        p->setPrevTerritorySize();

    /* ************************* */
    /*      Continent Bonus      */
    /* ************************* */
    // Get players number of territories
    int numberOfArmies = floor(p->getTerritorySize() / 3);

    // Find if the player owns all the territories of an entire contenent:
    int controlBonus = 0;
    bool ownsContinent = false;

    // Get all the continents then their territories:
    for (Continent *c : map->continentList)
    {
        int territoryCount = 0;
        controlBonus = c->controlBonus;
        vector<Territory *> listOfContentsTerritories = c->territories;
        // Loop through what the player has to check if the owns the full continent
        for (Territory *t : p->getTerritories())
        {
            // Count of how many of the players Territories we find of the continent
            if (find(listOfContentsTerritories.begin(), listOfContentsTerritories.end(), t) !=
                listOfContentsTerritories.end())
            {
                territoryCount++;
            }
        }

        // If both are equal sizes, then players owns continent.
        if (territoryCount == listOfContentsTerritories.size())
            ownsContinent = true;
        if (ownsContinent)
        {
            string bonusMsg = "\tcontinent bonus has been applied! adding an additional " + to_string(controlBonus) + " units\n";
            dprint(bonusMsg, section::reinforcement);
            numberOfArmies += controlBonus;
            ownsContinent = false;
        }
    }
    /* ************************************* */
    /*      Minimal Reinforcement to add     */
    /* ************************************* */
    // the minimal number of reinforcement armies per turn for any player is 3
    if (numberOfArmies < 3)
        numberOfArmies = 3;

    // placed in the player’s reinforcement pool.
    p->setReinforcementPool(p->getReinforcementPool() + numberOfArmies);
    string doneReinforcement = "Player: " + p->getName() + " has " + to_string(p->getReinforcementPool()) + " in his reinforcement pool.";

    dprint(doneReinforcement, section::reinforcement);
}

// returns false if someone is still issuing orders
bool GameEngine::allPlayersDone()
{
    for (Player *p : currentPlayers)
    {
        if (!p->isDoneIssuing())
            return false;
    }

    return true;
}

/*
   TODO: Implement put the logic of card creation in Strategy.issueOrder
*/
Order *createOrderFromCard(Card *card, Player *player, Territory *territorySrc, Territory *territoryTarget)
{
    return nullptr;
}

// void playerIssueOrder(Deck *deck, Player *issuingPlayer)
// {
//     if (issuingPlayer->isDoneIssuing())
//     {
//         // when done issueing deploy and advance, issue cards
//         // Bugs: commented out the creation of Orders from Cards
//         return void();
//     }
//     // (1) Deploy: until reinforc pool == 0
//     if (issuingPlayer->getReinforcementPool() > 0)
//     {
//         // cout << "Debug playerIssueOrder. Num of reinforcement pool: " << issuingPlayer->getReinforcementPool() << endl;
//         // Check if there is no more territory in priority queue -> rebuild it until pool is empty
//         if (issuingPlayer->getPriorityDefending().empty())
//         {
//             for (Territory *toDefend : issuingPlayer->toDefend())
//             {
//                 issuingPlayer->addToPriorityDefend(toDefend);
//             }
//         }
//         Territory *territoryTarget = issuingPlayer->getPriorityDefending().top();
//         // Create Deploy -> decrease reinforcement
//         Deploy *deploy = new Deploy(1, issuingPlayer, territoryTarget);
//         issuingPlayer->setReinforcementPool(issuingPlayer->getReinforcementPool() - 1);
//         // cout << "Issueing: " << deploy->getDetails() << endl;
//         issuingPlayer->issueOrder(deploy);
//         issuingPlayer->popPriorityDefend();
//     }
//     else // when no more reinforcementPool
//     {
//         // (3) Advance
//         if (issuingPlayer->isDoneDeploying() == false)
//         {
//             // This block should be entered only ONCE, before the first Advance order
//             issuingPlayer->setDoneDeploying(true);
//             issuingPlayer->getPriorityDefending() = priority_queue<Territory *, vector<Territory *>, compareArmySize>(); // clear queue
//             for (Territory *toDefend : issuingPlayer->toDefend())
//             {
//                 issuingPlayer->addToPriorityDefend(toDefend);
//             }
//         }
//         if (issuingPlayer->isDoneDeploying() and (issuingPlayer->getPriorityDefending().size() > 0 && issuingPlayer->getPriorityAttacking().size() > 0))
//         {
//             // Need to handle the case when the size of priorityAttack =/= size of priorityDefence => rebuild one or both queues depending on the strategy
//             Player *currentPlayer = issuingPlayer;
//             Territory *territorySource = currentPlayer->getPriorityDefending().top();
//             Territory *territoryTarget = currentPlayer->getPriorityAttacking().top(); // problem is empties before priorityDefending
//             Advance *advance = new Advance((territorySource->getNumberOfArmies() / 2), currentPlayer, territorySource, territoryTarget);
//             // cout << "Issueing! " << advance->getDetails() << endl;
//             currentPlayer->issueOrder(advance);
//             currentPlayer->popPriorityAttack();
//             currentPlayer->popPriorityDefend();
//         }
//         // check if no more advance order can be created -> set isDone flag to true
//         if (issuingPlayer->getPriorityDefending().size() == 0 || issuingPlayer->getPriorityAttacking().size() == 0)
//         {
//             issuingPlayer->toggleDoneIssuing();
//             // cout << "Finished issueing Deploy and Advance. isDone flag is set to " << to_string(issuingPlayer->isDoneIssuing()) << endl;
//         }
//     }
// }

void GameEngine::issueOrdersPhase()
{
    // For turn 2 and on, need to reset player's queues and flags
    /*
        - doneIssuing is set to false
        - doneDeploying is set to false
        - doneAdvancing is set to false (?)
        - rebuilding the priority queues
    */

    for (Player *p : currentPlayers)
    {
        p->setDoneIssuing(false);
        p->setDoneDeploying(false);

        // Debugging: show current content of toAttack and toDefend before each issueOrdersPhase
        string showToAttack = "Start of issueOrderPhase : player " + p->getName() + "'s toAttack = ";
        for (Territory *toAttack : p->toAttack())
        {
            p->addToPriorityAttack(toAttack);
            showToAttack += toAttack->getName() + "(" + to_string(toAttack->getNumberOfArmies()) + ")" + ", ";
        }
        string showToDefend = "Start of issueOrderPhase : player " + p->getName() + "'s toDefend = ";
        for (Territory *toDefend : p->toDefend())
        {
            p->addToPriorityDefend(toDefend);
            showToDefend += toDefend->getName() + "(" + to_string(toDefend->getNumberOfArmies()) + ")" + ", ";
        }
        dprint(showToAttack, section::issueorder);
        dprint(showToDefend, section::issueorder);
        dprint("\n\n", section::issueorder);
    }
    while (!allPlayersDone())
    {
        for (int i = 0; i < currentPlayers.size(); )
        {
            dprint("\nGameEngine:: Player " + currentPlayers.at(i)->getName() + " is now entering playerIssueOrder method.\n", section::issueorder);

            currentPlayers.at(i)->issueOrder();
        }
        // Cannot iterate through players normally while erasing players as they lose
        // std::vector<int> v = {1, 2, 3, 4, 5, 6};

        // auto player = currentPlayers.begin();
        // while (player != currentPlayers.end())
        // {
        //     // remove odd numbers
        //     if (*player & 1)
        //     {
        //         // `erase()` invalidates the iterator, use returned iterator
        //         it = v.erase(it);
        //     }
        //     // Notice that the iterator is incremented only on the else part (why?)
        //     else
        //     {
        //         ++it;
        //     }
        // }

        // for (int const &i : v)
        // {
        //     std::cout << i << ' ';
        // }
    }
}

bool hasOrders(vector<Player *> currentPlayers)
{
    for (Player *player : currentPlayers)
    {
        if (player->getOrderList()->getList().size() != 0)
            return true;
    }
    return false;
}

void GameEngine::executeOrdersPhase()
{
    // players have signified that they are not issuing one more order
    bool hasDeploy = false;

    // Debugging: display all players' orders before starting execution
    for (auto p : currentPlayers)
    {
        std::stringstream buffer;
        buffer << "Orders issues for player " << p->getName() << " = ";
        buffer << *p->getOrderList() << "\n";
        dprint(buffer.str(), section::execorder);
    }

    while (hasOrders(currentPlayers))
    {
        // Iterate over each player
        for (int i = 0; i < currentPlayers.size(); i++)
        {
            Player *currentPlayer = currentPlayers.at(i);
            bool played = false;

            // Debug flag
            string numOrdersLeftMsg = "\tGameEngine:: Player: " + currentPlayer->getName() + " has " + to_string(currentPlayer->getOrderList()->getList().size()) + " left orders to execute. ";
            dprint(numOrdersLeftMsg, section::execorder);

            // Check if player still has order to execute, if not, skip iteration
            if (currentPlayer->getOrderList()->getList().size() == 0)
            {
                dprint(currentPlayer->getName() + " is done executing. Skip.", section::execorder);
                continue;
            }

            // TODO: refactor this Order execution
            if (currentPlayer->getOrderList()->getList().at(0)->getCommand() == "Deploy type")
            {
                for (Order *order : currentPlayers.at(i)->getOrderList()->getList())
                {
                    if (order->getCommand() == "Deploy type")
                    {
                        dprint("\t" + currentPlayer->getName() + " issues deploy " + "\t==> " + order->getDetails(), section::execorder);
                        order->execute();
                        played = true;
                        break;
                    }
                }
            }

            else
            {
                for (Order *order : currentPlayers.at(i)->getOrderList()->getList())
                {
                    dprint("\t" + currentPlayer->getName() + " issues non-deploy " + order->getDetails(), section::execorder);
                    order->execute();
                    played = true;
                    break;
                }
            }

            // Remove it from the list of orders
            if (currentPlayers.at(i)->getOrderList()->getList().size() != 0)
                currentPlayers.at(i)->getOrderList()->remove(0);
        }
    }

    // ! Do not transition to assignreinforcement state yet: need to check for winners (done in the driver function)
}

/* ***************************************************************************************************************************** */
/*                                                   Main Game Loop : Driver
/* ***************************************************************************************************************************** */

// Rewriting the mainLoop test as a free function
void riskGameDriver()
{
    bool stillPlaying = true;

    while (stillPlaying)
    {
        GameEngine *engine = new GameEngine(); // need to re-instantiate engine after each game (else, segmentation fault error... badly defined GameEngine Constructors?)

        dprint("Debug: Entering StartUp phase", section::all);
        engine->preStartup();

        dprint("Debug: Entering mainGamePlay phase", section::all);
        engine->mainGameLoop();
        dprint("Debug: Exiting mainGamePlay phase", section::all);

        if (engine->getCurrentStateName() == "start")
        {
            pressToContinueWith("REPLAY");
        }
        else if (engine->getCurrentStateName() == "final")
        {
            pressToContinueWith("END GAME");
            stillPlaying = false;
            break;
        }
        else
        {
            dprint("Problem with riskGameDriver... This is an invalid state", section::all);
        }

        // delete engine; // todo: GameEngine destructor ? gives malloc error...
    }

    cout << "Exiting the program. Thanks for playing!" << endl;
}

void GameEngine::mainGameLoop()
{

    bool noWinner = true;
    // Keeping track of turns for tournament mode
    int maximumNumberOfTurns = 50;
    int numOfTurns = 0;
    // while (noWinner && (numOfTurns < maximumNumberOfTurns))
    while (noWinner)
    {

        /* ****************************** */
        /* PHASE 1: Reinforcement Phase   */
        /* ****************************** */
        // this->doTransition("gamestart");
        for (Player *p : currentPlayers)
        {
            dprint("Player " + p->getName() + " entering GameEngine::reinforcementPhase ...", section::mainGameLoop);
            reinforcementPhase(p);
            dprint("Player " + p->getName() + " finished GameEngine::reinforcementPhase successfully", section::mainGameLoop);
        }
        dprint("Exited GameEngine::reinforcementPhase successfully", section::mainGameLoop);

        /* ***************************** */
        /* PHASE 2: Issue Orders Phase   */
        /* ***************************** */

        {
            this->doTransition("issueorder");
            issueOrdersPhase();
            dprint("Exited GameEngine::issueOrdersPhase successfully", section::mainGameLoop);
            this->doTransition("endissueorders");
        }

        /* ****************************** */
        /* PHASE 3: Execute Orders Phase  */
        /* ****************************** */
        {
            this->doTransition("execorder");
            executeOrdersPhase();
            dprint("Exited GameEngine::executeOrderPhase successfully", section::mainGameLoop);
        }

        Player *winner = 0;
        for (auto p : getPlayers())
        {
            if (p->getTerritories().size() == getMap()->getTerritorySize())
                winner = p;
        }
        if (winner != 0)
        {
            this->doTransition("win");
            cout << " ****************************************** " << endl;
            cout << "\nPlayer " << winner->getName() << " won the game!" << endl;

            // Show the territories conquered by winner and the territories owned by losers (should be none)
            for (auto p : getEliminatedPlayers()) // loop for players who were audited out
            {
                cout << p->getName() << " conquered territories = (";
                for (auto t : p->getTerritories())
                {
                    cout << t->getName() << ", ";
                }
                cout << ")" << endl;
            }
            for (auto p : getPlayers()) // loop for last 2 players in the game
            {
                cout << p->getName() << " conquered territories = (";
                for (auto t : p->getTerritories())
                {
                    cout << t->getName() << ", ";
                }
                cout << ")" << endl;
            }
            cout << "Do you wish to replay? (y/n)" << endl;
            string input;
            cin >> input;
            if (input == "y")
            {
                doTransition("replay");
            }
            else if (input == "n")
            {
                doTransition("quit");
            }
            cout << getCurrentStateName() << endl;

            break; // get out of main game play loop
        }
        else
        {
            // this transition only happen when there is no winner after end of order execution
            this->doTransition("endexecorders");
            auditPlayers(); // remove players who lost

            // stay in main game loop
        }

        numOfTurns++;
        string endOfTurnMsg = "End of turn " + to_string(numOfTurns) + "\n";
        dprint(endOfTurnMsg, section::mainGameLoop);
        pressToContinueWith("TURN");
    }

    // To delete
    // std::exit(0);
}

/* **************************************** */
/*           /(•̀o•́)ง                        */
/*   (ง'̀-'́)ง  Tournament mode  (ง•̀o•́)ง   */
/*    (๑•̀ᗝ•́)૭               (ง°ل͜°)ง       */
/* **************************************** */

// Format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
void GameEngine::enterTournamentMode(Command *command)
{
    vector<string> args = command->getArgs();
    vector<string> mapFileNames = {};
    vector<string> playerTypes = {};
    int numOfGames = 0;
    int numOfTurns = 0;
    try
    {
        for (int i = 0; i < command->getArgs().size();)
        {
            // extract args
            if (args[i] == "-M")
            {
                // while we haven't reached another -
                i++;
                while (args[i].find('-') == std::string::npos)
                {
                    mapFileNames.push_back(args[i]);
                    i++;
                }
            }
            else if (args[i] == "-P")
            {
                // while we haven't reached another -
                i++;
                while (args[i].find('-') == std::string::npos)
                {
                    playerTypes.push_back(args[i]);
                    i++;
                }
            }
            else if (args[i] == "-G")
            {
                numOfGames = std::stoi(args[++i]);
            }
            else if (args[i] == "-D")
            {
                numOfTurns = std::stoi(args[++i]);
            }
            else
            {
                i++;
            }
        }
    }
    catch (exception &e)
    {
        cout << e.what();
        exit(0);
    }

    // TODO: create player types + load the maps, add it to the gameEngine players and maps
    for (int i = 0; i < numOfGames; i++)
    {
        for (int j = 0; j < mapFileNames.size(); j++)
        {
            // TODO: load map here
            StartupPhase sp;
            sp.setGameEng(this);
            sp.startup();
            mainGameLoop();
        }
    }
    exit(0);
}
