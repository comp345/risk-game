#include <iostream>
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

namespace fs = filesystem;
using namespace std;

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

//using default value
GameEngine::GameEngine(std::string newFile)
{
    // Create the states and add to states collection
    initStates();

    //Initialization
    currentPlayers = vector<Player *>();
    initializedRand(); // randomize deck
    deck = new Deck(30);
    validTransition = false;
    if (newFile.empty()) {
        commandProcessor = new CommandProcessor();
    } else {
        commandProcessor = new FileCommandProcessorAdapter(newFile);
    }
}


void GameEngine::initStates() {
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
}

/* TODO */
GameEngine::~GameEngine()
{
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
    return ""; //TODO: throw exception
}

// Makes the engine transitions to the next state if command is valid. Returns boolean to help debugging or more validation
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


string GameEngine::stringToLog() {
    return "GameEngine transitioned to a new state: " + currentState->nameState;
}


//helper methods
Map *GameEngine::getMap() {
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
{ //for randomizing players order of appearance on gamestart
    shuffle(begin(currentPlayers), end(currentPlayers), default_random_engine{});
    cout << "players shuffled...\n"
         << endl;
}

vector<Player *>& GameEngine::getPlayers()
{
    return currentPlayers;
}

void GameEngine::getMapList()
{ //helper method for loading list of maps from the directory in an ordered list
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

Deck * GameEngine::getDeck()
{
    return deck;
}

/* ****************************************************************** */
/* ***************  Command Processor Driver for A2  **************** */
/* ****************************************************************** */
// A2 Part 1: Command Processor
void GameEngine::testGameEngine()
{
    Command *output;
    cout << "Welcome to WarZone!" << endl;
    while (true)
    {
        //To handle replay case, getCommand has to be called at a later execution
        output = commandProcessor->getCommand(currentState);
        doTransition(output->getCommandName());
        if (output->getCommandName() == "gamestart")
        {
            //Start the gameloop
            break;
        }
        else if (output->getCommandName() == "replay")
        {
            //Call me later
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
/* ***************  Startup Phase Driver and helper functions  **************** */
/* **************************************************************************** */

// Two main phases
void GameEngine::preStartup() {
    Command *command;

    do {
        command = commandProcessor->getCommand(currentState);
    } while (command->getArgs().empty() || !doTransition(command->getCommandName()));

    if (currentState->nameState == "tournament") {
        enterTournamentMode(command);
    }

    // starting with loadmap
    string path = "../maps/";
    MapLoader *mapLoader = new MapLoader();
    cout << "Initiating map loading stage: \n"
         << endl;
    getMapList();

    string mapName = command->getArgs()[0];
    cout << "current command: " << command->getCommandName() << "\n" << endl;
    cout << "current mapfile requested: " << mapName << "\n" << endl;

    string fpath = path.append(mapName);
    Map x1 = *mapLoader->loadMap(fpath);
    Map *map1 = new Map(x1);
    cout << "Map " << mapName << " has been loaded. \n" << endl;

    do {
        command = commandProcessor->getCommand(currentState);
    } while (!doTransition(command->getCommandName()));

    map1->validate();// validates map
    map1->showLoadedMap();
    setMap(map1);

    // addplayer loop
    while (true) {
        do {
            command = commandProcessor->getCommand(currentState);
        } while (command->getArgs().empty() || !doTransition(command->getCommandName()));
        string cmdPlName = command->getArgs()[0];

        numberOfPlayers++;
        setNumOfPlayers(numberOfPlayers);
        Player *p = new Player();
        p->setPlName(cmdPlName);
        p->setReinforcementPool(5);
        cout << *p << "Number of Armies: " << p->getReinforcementPool() << endl;
        cout << "Cards in players hand: " << p->getHand() << endl; //TODO: prints address
        currentPlayers.push_back(p);

        cout << "total number of players so far is: " << getNumOfPlayers() << endl;
        if (getNumOfPlayers() == 1) {
            cout << "have 1 player so far" << endl;
            continue;
        }
        if (getNumOfPlayers() < 7 && commandProcessor->fileName.empty()) {
            cout << "continue adding players? (y/n)" << endl;
            string keyInY;
            getline(cin, keyInY);
            if (keyInY == "y") {
                continue;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    do {
        command = commandProcessor->getCommand(currentState);
    } while (!doTransition(command->getCommandName()));

    StartupPhase sp;
    sp.setGameEng(this);
    sp.startup();
}

//startupPhase methods
StartupPhase::StartupPhase()
{
    eng = new GameEngine();
}

StartupPhase::StartupPhase(const StartupPhase &sp)
{
    this->eng = sp.eng;
}

StartupPhase::~StartupPhase() {
    //TODO: missing destructor
}

void StartupPhase::operator=(const StartupPhase &sp)
{
    eng = sp.eng;
}

ostream &operator<<(ostream &out, const StartupPhase &sp) {
    //out<<"\nGame Engine: "<<sp.eng<< endl;//TODO: fix
    return out;
}

std::istream &operator>>(std::istream &in, const StartupPhase &sp) {
    //in>>sp.eng; //TODO: fix
    return in;
}

void StartupPhase::setGameEng(GameEngine *en)
{
    eng = en;
}

void StartupPhase::startup() {
    //randomizing players order
    vector<Player *>& players = eng->getPlayers();
    cout << "Randomize player order: \n" << endl;
    eng->randomizePlayersTurn();
    cout << "Current order of players after randomize: \n" << endl;
    for (Player *p: players) {
        cout << *p << "----" << endl;
    }

    //giving armies to players:
    cout << "Starting Army distribution for players: \n" << endl;
    for (int i = 0; i < eng->getNumOfPlayers(); i++) {
        players[i]->setReinforcementPool(50);
    }
    cout << "Players have received 50 army each! \n" << endl;
    for (Player *p: players) {
        cout << "player " << p->getName() << ": " << p->getReinforcementPool() << endl;
    }

    //letting players draw 2 cards
    for (Player *p: players) {
        Hand *h = new Hand();
        p->setCards(h);
        Deck* deck = eng->getDeck();
        for (int i = 0; i <= 2; i++) {
            deck->draw(*p);
        }
        cout << p->getName() << " drew 2 cards!" << endl;
    }

    //territory assignment
    cout << "Distributing territories to the players: \n"
         << endl;
    Map *map = eng->getMap();
    if (!map->territoryNodeList.empty())
    {
        shuffle(begin(map->territoryNodeList), end(map->territoryNodeList), default_random_engine());

        while (!map->territoryNodeList.empty())
        {
            vector<Player *>& players = eng->getPlayers();
            for (Player *p : players)
            {
                if (!map->territoryNodeList.empty())
                {
                    vector<Territory *> territories;
                    territories.push_back(map->territoryNodeList.back());
                    p->addTerritories(territories);
                    map->territoryNodeList.pop_back();
                    for (Territory *t: territories) { // Bug: only one territory is assigned to each player...
                        t->setOwner(p);
                    }
                }
            }
        }
        //for displaying players with acquired territories
        for (Player *p : eng->getPlayers()) // getPlayers() returns a vector&
        {
            cout << *p << endl;
        }
    }
    else
    {
        cout << "The map has loading problems" << endl;
    }
}

/* ********************************************************************** */
/* ***************  Helper functions for Main Game Loop  **************** */
/* ********************************************************************** */
bool checkWinCondition()
{
    // Check if there is a player who wons every territory in map
    return false;
}

void GameEngine::auditPlayers() {
    for (Player *p: currentPlayers) {
        if (p->getTerritories().size() == 0) {
            cout << "\nPlayer " << p->getName()
                 << " no longer has any territories left and will be removed from the game \n";

            currentPlayers.erase(remove(currentPlayers.begin(), currentPlayers.end(), p));

            delete p;
            p = NULL;
        }
    }
}

Player *GameEngine::hasWinner() {
    //Get the players territories
    for (Player *p: currentPlayers) {

        if (map->getTerritories().size() == p->getTerritories().size()) {
            return p;
        }
    }

    return NULL;
}

void GameEngine::reinforcementPhase(Player *p)
{
     
    /* ******************* */
    /*      Card Bonus     */
    /* ******************* */
    // Check if player won territories in the last round. If yes, draw one card max
    int numConqueredTerritories = p->getTerritorySize() - p->getPrevTerritorySize();
    if (numConqueredTerritories > 0)
        deck->draw(*p);

    // update prevTerritorySize
    p->setPrevTerritorySize();


    /* ************************* */
    /*      Continent Bonus      */
    /* ************************* */
    //Get players number of territories
    int numberOfArmies = floor(p->getTerritorySize() / 3);

    //Find if the player owns all the territories of an entire contenent:
    int controlBonus = 0;
    bool ownsContinent = false;

    //Get all the continents then their territories:
    for (Continent *c: map->continentList) {
        int territoryCount = 0;
        controlBonus = c->controlBonus;
        vector<Territory *> listOfContentsTerritories = c->territories;

        //Loop through what the player has to check if the owns the full continent
        for (Territory *t: p->getTerritories()) {

            //Count of how many of the players Territories we find of the continent
            if (find(listOfContentsTerritories.begin(), listOfContentsTerritories.end(), t) !=
                listOfContentsTerritories.end()) {
                territoryCount++;
            }
        }

        //If both are equal sizes, then players owns continent.
        if (territoryCount == listOfContentsTerritories.size())
            ownsContinent = true;

        if (ownsContinent) {
            cout << "continent bonus has been applied! adding an additional " << controlBonus << " units";
            numberOfArmies += controlBonus;
            ownsContinent = false;
        }
    }

    /* ************************************* */
    /*      Minimal Reinforcement to add     */
    /* ************************************* */
    //the minimal number of reinforcement armies per turn for any player is 3
    if (numberOfArmies < 3)
        numberOfArmies = 3;

    // placed in the player’s reinforcement pool.
    p->setReinforcementPool(p->getReinforcementPool() + numberOfArmies);
}

// returns false if someone is still issuing orders
bool GameEngine::allPlayersDone() {
    for (Player *p: currentPlayers) {
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
    string checkTypeCard = card->getCommand();

    if (checkTypeCard == "Airlift type") {
        cout << "... player desires to create an AirLift order by using a valid card!..." << endl;
        if (!territoryTarget or !territorySrc)
            throw std::exception();
        AirLift *a = new AirLift(1, player, territorySrc, territoryTarget);
        cout << a->getDetails() << endl;
        return a;
    }

    if (checkTypeCard == "Bomb type") {
        cout << "... player desires to create a Bomb order by using a valid card!..." << endl;

        if (!territoryTarget)
            throw std::exception();
        Bomb *b = new Bomb(player, territoryTarget);
        cout << b->getDetails() << endl;
        return b;
    }
    if (checkTypeCard == "Blockade type")
    {
        if (!territorySrc)
            throw std::exception();
        Blockade *b = new Blockade(territorySrc, player, new Player("neutral (hardcoded)"));
        cout << b->getDetails() << endl;
        return b;
    }
    if (checkTypeCard == "Diplomacy type")
    {
        Negotiate *n = new Negotiate(player, new Player("enemy (hardcoded)"));
        cout << n->getDetails() << endl;
        return n;
    }
    if (checkTypeCard == "Reinforcement type")
    {
        // TODO: add to player's reinforcement pool
        return nullptr;
    }
    else
    {
        cout << "== DEBUG in: creatingOrderFromCard. Card is not valid!? ==";
        cout << checkTypeCard << endl;
        return nullptr;
    }
}

void playerIssueOrder(Deck *deck, Player *issuingPlayer)
{
    // when done issueing deploy and advance, issue cards
    // Bugs: commented out the creation of Orders from Cards

    if (issuingPlayer->isDoneIssuing())
    {
        // // When done issuing orders, start issuing 1 card order per turn until both player are done...
        // // flawed but will work
        // Player *player = issuingPlayer;
        // cout << "DEBUG: Player " << player->getName() << " wants to play card..." << endl;
        // if (player->getHand()->getCards().size() > 0)
        // {
        //     Territory *territorySrc = new Territory;
        //     Territory *territoryTarget = new Territory;
        //     if (player->getPriorityDefending().size() > 0)
        //     {
        //         territorySrc = player->popPriorityDefend();
        //     }
        //     else
        //     {
        //         territorySrc = nullptr;
        //     }
        //     if (player->getPriorityAttacking().size() > 0)
        //     {
        //         territoryTarget = player->popPriorityAttack();
        //     }
        //     else
        //     {
        //         territoryTarget = nullptr;
        //     }
        //     // Card *lastCard = player->getHand()->useLast();
        //     // Player &playerRef = *player;
        //     // Deck &deckRef = *deck;
        //     // lastCard->play(playerRef, deckRef); // return card to deck

        //     try
        //     {
        //         // Method throws exception to handle
        //         // createOrderFromCard(lastCard, player, territorySrc, territoryTarget);
        //         cout << " ... played a card... " << endl;
        //     }
        //     catch (std::exception e)
        //     {
        //         cout << "Cannot create special order from card (not enough resources)" << endl;
        //     }
        // }

        return void();
    }

    // (1) Deploy: until reinforc pool == 0
    /*
        Problem:
        what is there are more armies in the reinforcement pool than there are territory?
    */
    if (issuingPlayer->getReinforcementPool() > 0)
    {
        cout << "Debug playerIssueOrder. Num of reinforcement pool: " << issuingPlayer->getReinforcementPool() << endl;
        // Check if there is no more territory in priority queue -> rebuild it until pool is empty
        if (issuingPlayer->getPriorityDefending().empty()) 
        {
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        Territory *territoryTarget = issuingPlayer->getPriorityDefending().top();

        // Create Deploy -> decrease reinforcement
        Deploy *deploy = new Deploy(1, issuingPlayer, territoryTarget);
        issuingPlayer->setReinforcementPool(issuingPlayer->getReinforcementPool() - 1);

        cout << "Issueing: " << deploy->getDetails() << endl;
        issuingPlayer->issueOrder(deploy);
        issuingPlayer->popPriorityDefend();
    }
    else // when no more reinforcementPool
    {
        // (3) Advance
        /*TODO: Before the first issueing of an Advance order
            - Put Player::isDoneDeploying flag to TRUE 
            - Rebuild the defending priority queue after deploying phase is done
        */
        if (issuingPlayer->isDoneDeploying() == false)
        {
            // This block should be entered only ONCE, before the first Advance order
            issuingPlayer->setDoneDeploying(true);
            issuingPlayer->getPriorityDefending() = priority_queue<Territory *, vector<Territory *>, compareArmySize>(); // clear queue
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        if (issuingPlayer->isDoneDeploying() and (issuingPlayer->getPriorityDefending().size() > 0 && issuingPlayer->getPriorityAttacking().size() > 0))
        {
            // Need to handle the case when the size of priorityAttack =/= size of priorityDefence => rebuild one or both queues depending on the strategy
            Player *currentPlayer = issuingPlayer;
            Territory *territorySource = currentPlayer->getPriorityDefending().top();
            Territory *territoryTarget = currentPlayer->getPriorityAttacking().top(); // problem is empties before priorityDefending
            Advance *advance = new Advance(1, currentPlayer, territorySource, territoryTarget);
            cout << "Issueing! " << advance->getDetails() << endl;
            currentPlayer->issueOrder(advance);
            currentPlayer->popPriorityAttack();
            currentPlayer->popPriorityDefend();
        }
        // check if no more advance order can be created -> set isDone flag to true
        if (issuingPlayer->getPriorityDefending().size() == 0 || issuingPlayer->getPriorityAttacking().size() == 0)
        {
            issuingPlayer->toggleDoneIssuing();
            cout << "Finished issueing Deploy and Advance. isDone flag is set to " << to_string(issuingPlayer->isDoneIssuing()) << endl;
        }
    }
        
}

void GameEngine::issueOrdersPhase()
{
    // For turn 2 and on, need to reset player's fields and flags
    /*
        - doneIssuing is set to false
        - doneDeploying is set to false
        - doneAdvancing is set to false (?)
        - rebuilding the priority queues 
    */

    // Updating each players' toAttack and toDefend queues
    for (Player *p : currentPlayers)
    {
        // set isDone flag to false
        p->setDoneIssuing(false);

        // set isDoneDeploying flag to false
        p->setDoneDeploying(false);

        // Debugging: why no Advance Orders are created
        cout << endl << "= Start of issueOrderPhase : player " << p->getName() << "'s toAttack = ";
        for (Territory *toAttack : p->toAttack())
        {
            p->addToPriorityAttack(toAttack);
            cout << toAttack->getName() << ", ";
        }

        //Debugging
        cout << endl << "= Start of issueOrderPhase : player " << p->getName() << "'s toDefend = ";
        for (Territory *toDefend : p->toDefend())
        {
            p->addToPriorityDefend(toDefend);
            cout << toDefend->getName() << ", ";
        }
        cout << endl << endl;
    }
    while (!allPlayersDone())
    {
        for (int i = 0; i < currentPlayers.size(); i++)
        {
            cout << "\nGameEngine:: Player: " << currentPlayers.at(i)->getName() << " is currently in the issue order phase.\n";

            // Free function to implement as Player::issueOrder
            playerIssueOrder(this->deck, currentPlayers.at(i));
        }
    }
}

bool hasOrders(vector<Player *> currentPlayers) {
    for (Player *player: currentPlayers) {
        if (player->getOrderList()->getList().size() != 0)
            return true;
    }
    return false;
}

void GameEngine::executeOrdersPhase() {
    //players have signified that they are not issuing one more order
    bool hasDeploy = false;

    // Debugging: display all players' orders before starting execution
    for (auto p : currentPlayers)
    {
        cout << "Orders issues for player " << p->getName() << " = ";
        cout << *p->getOrderList() << endl;
    }

    while (hasOrders(currentPlayers))
    {
        //Iterate over each player
        for (int i = 0; i < currentPlayers.size(); i++) {
            Player *currentPlayer = currentPlayers.at(i);
            bool played = false;

            // Debug flag
            cout << endl
                 << "\tGameEngine:: Player: " << currentPlayer->getName()
                 << " has " << currentPlayer->getOrderList()->getList().size() << " left orders to execute. " << endl;

            // Check if player still has order to execute, if not, skip iteration
            if (currentPlayer->getOrderList()->getList().size() == 0)
            {
                cout << endl
                     << currentPlayer->getName() << " is done executing. Skip." << endl;

                continue; // ! bug?
            }

            if (currentPlayer->getOrderList()->getList().at(0)->getCommand() == "Deploy type")
            {
                for (Order *order : currentPlayers.at(i)->getOrderList()->getList())
                {
                    if (order->getCommand() == "Deploy type")
                    {
                        cout << "\t" << currentPlayer->getName() << " will be issueing an order:";
                        cout << "\t==>" << order->getDetails() << endl;
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
                    cout << "\t" << currentPlayer->getName() << " will be issueing an order:";
                    cout << "==>" << order->getDetails() << endl;
                    order->execute();
                    played = true;
                    break;
                }
            }

            //Remove it from the list of orders
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

        cout << "Debug: Entering StartUp phase" << endl;
        engine->preStartup();

        cout << "Debug: Entering mainGamePlay phase" << endl;
        engine->mainGameLoop();
        cout << "Debug: Exiting mainGamePlay phase" << endl;

        if (engine->getCurrentStateName() == "start")
        {
            cout << "Debug: replay ... (press any keys to continue)" << endl;

            string x;
            cin >> x;
        }
        else if (engine->getCurrentStateName() == "final")
        {
            cout << "Debug: End game ... " << endl;
            stillPlaying = false;
            break;
        }
        else
        {
            cout << "There is a bug... program should end or trigger the startUp, or there is no winner" << endl;
        }
    }

    cout << "Debug: Exiting the program. Thanks for playing!" << endl;
}

void GameEngine::mainGameLoop()
{

    bool noWinner = true;
    // Keeping track of turns for tournament mode
    int maximumNumberOfTurns = 5;
    int numOfTurns = 0;
    while (noWinner && (numOfTurns < maximumNumberOfTurns))
    {

        /* ****************************** */
        /* PHASE 1: Reinforcement Phase   */
        /* ****************************** */
        // this->doTransition("gamestart");
        for (Player *p : currentPlayers)
        {
            reinforcementPhase(p);
            cout << "\nPlayer: " << p->getName() << " has " << p->getReinforcementPool() << " in his reinforcement pool.\n";
        }

        /* ***************************** */
        /* PHASE 2: Issue Orders Phase   */
        /* ***************************** */

        {
            this->doTransition("issueorder");
            issueOrdersPhase();
            this->doTransition("endissueorders");
        }

        /* ****************************** */
        /* PHASE 3: Execute Orders Phase  */
        /* ****************************** */
        {
            this->doTransition("execorder");
            executeOrdersPhase();
            // cout << "reached outside execution order" << endl;
        }

        Player *winner = hasWinner();

        // Forcing a win
        // winner = new Player("TESTING WIN");
        cout << "Debug winner = " << winner << endl;

        if (winner != nullptr)
        {
            this->doTransition("win");
            cout << "\nPlayer " << winner->getName() << " won the game! Do you wish to replay? (y/n)\n";

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
    }

    // To delete
    std::exit(0);
}

// Format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
void GameEngine::enterTournamentMode(Command *command) {
    vector<string> args = command->getArgs();
    vector<string> mapFileNames = {};
    vector<string> playerTypes = {};
    int numOfGames = 0;
    int numOfTurns = 0;
    try {
        for (int i = 0; i < command->getArgs().size();) {
            //extract args
            if (args[i] == "-M") {
                //while we haven't reached another -
                i++;
                while (args[i].find('-') == std::string::npos) {
                    mapFileNames.push_back(args[i]);
                    i++;
                }
            } else if (args[i] == "-P") {
                //while we haven't reached another -
                i++;
                while (args[i].find('-') == std::string::npos) {
                    playerTypes.push_back(args[i]);
                    i++;
                }
            } else if (args[i] == "-G") {
                numOfGames = std::stoi(args[++i]);
            } else if (args[i] == "-D") {
                numOfTurns = std::stoi(args[++i]);
            } else {
                i++;
            }
        }
    } catch (exception& e) {
        cout << e.what();
        exit(0);
    }

    for (int i = 0; i < numOfGames; i++) {
        StartupPhase sp;
        sp.setGameEng(this);
        sp.startup();
        mainGameLoop();
    }
    exit(0);
}
