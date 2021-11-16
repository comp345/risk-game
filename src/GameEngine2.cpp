#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include "GameEngine2.h"
#include "Map.h"

namespace fs = filesystem;


State::State() {
    nameState = "";
}

State::State(string name) {
    nameState = name;
}

State::State(string name, vector<Transition *> t) {
    nameState = name;
    transitions = t;
}

State::State(const State &s) {
    nameState = s.nameState;
    transitions = vector<Transition *>(
            s.transitions); // Using vector copy constructor! Works, demonstration in testGameEngine
}

State::~State() {
    transitions.clear();
}

State &State::operator=(const State &c) {
    if (this == &c)
        return *this;
    this->nameState = c.nameState;
    this->transitions = c.transitions; // Using the vector assignment operator
    return *this;
}

void State::addTransition(Transition *t) {
    transitions.push_back(t);
}

Transition::Transition() {
    nameTransition = "";
    nextState = nullptr;
}

Transition::Transition(string name) {
    nameTransition = name;
    nextState = nullptr;
}

Transition::Transition(string name, State *s) {
    nameTransition = name;
    nextState = s;
}

Transition::Transition(const Transition &t) {
    nameTransition = t.nameTransition;
    nextState = new State(*(t.nextState));
}

Transition::~Transition() {
    delete nextState;
}

Transition &Transition::operator=(const Transition &t) {
    if (this == &t)
        return *this;
    this->nameTransition = t.nameTransition;
    this->nextState = new State(*(t.nextState));
    return *this;
}

// Creates the finite state machine that contains states and transitions
// The GameEngine object has access to the current state with getCurrentState(), as well
// as the valid transitions from that state with getCurrentPossibleTransitions()
GameEngine::GameEngine() {
    // Create the states and add to states collection

    State *startState = new State("start");
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

    commandProcessor = new CommandProcessor();
    isFile = false;
}

GameEngine::GameEngine(std::string newFile)
{
    // Create the states and add to states collection
    State *startState = new State("start");
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

    // Create Adapter and pass file
    fileName = newFile;
    fileAdapter = new FileCommandProcessorAdapter(newFile);
    isFile = true;
}


string GameEngine::getCurrentStateName() {
    return currentState->nameState;
}

vector<string> GameEngine::getNextTransitions() {
    vector<string> transitionsNames;
    for (int i = 0; i < currentState->transitions.size(); ++i) {
        transitionsNames.push_back(currentState->transitions.at(i)->nameTransition);
    }
    return transitionsNames;
}

string GameEngine::getNextStateName(string command) {
    for (int i = 0; i < currentState->transitions.size(); ++i) {
        if (currentState->transitions.at(i)->nameTransition == command) {
            return currentState->transitions.at(i)->nextState->nameState;
        }
    }
    return ""; //TODO: throw exception
}

// Check if command is valid. If it is, updates the state. Return true if command was valid, false if else.
// The success and error messages are not implemented, to allow flexible implementation in differents parts of A2.
bool GameEngine::doTransition(string command)
{
    // cout << "Ending up gettin gin the gameengine transtion " << std::endl;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            *currentState = *currentState->transitions.at(i)->nextState;
            return true;
        }
    }
    return false;
}

// Game play implementation for A1.
// TODO: Will need to divide game flow into StartUpPhase(), GameLoopPhase(), etc. for A2
void GameEngine::testGameEngine()
{
    //GameEngine engine{fileName};
    Command* output;
    cout << "Welcome to WarZone!" << endl;

   //Different execution depending if -f arg is passed
    if(!isFile)
    {
        while(true)
        {
            //To handle replay case, getCommand has to be called at a later execution
            output = commandProcessor->getCommand(currentState);
            doTransition(output->getCommandName());
            if(output->getCommandName() == "gamestart")
            {
                //Start the gameloop
                break;
            }
            else if(output->getCommandName() == "replay")
            {
                //Call me later
                cout << "\n";
            }
            else if(output->getCommandName() == "quit")
                exit(0);
            cout << "\n";
        }
    cout << "\n";
    cout << "Voila tous les commands: " << endl;
    commandProcessor->printCommands();
    }
    else
    {
        while(true)
        {
            output = fileAdapter->getCommand(currentState);
            doTransition(output->getCommandName());
            if(output->getCommandName() == "gamestart")
            {
                //Start the gameloop
                break;
            }
            else if(output->getCommandName() == "quit")
               exit(0);
            cout << "\n";
        }
    cout << "\n";
    cout << "Voila tous les commands: " << endl;
    fileAdapter->printCommands();
    }
}

string GameEngine::stringToLog() {
    return "TODO";
}

/**
 * @A2 Part 2 
 * 
 */

// Helper functions
bool checkWinCondition() {
    // Check if there is a player who wons every territory in map
    return false;
}

void GameEngine::reinforcementPhase() {}

void GameEngine::issueOrdersPhase() {}

void GameEngine::executeOrdersPhase() {}

//helper methods
Map *GameEngine::getMap() {
    cout << "got map!\n" << endl;
    return map;
}

int GameEngine::getNumOfPlayers() {
    return numberOfPlayers;
}

void GameEngine::setNumOfPlayers(int plNumb) {
    numberOfPlayers = plNumb;
}

void GameEngine::randPlVec() {//for randomizing players order of appearance on gamestart
    shuffle(begin(plVec), end(plVec), default_random_engine{});
    cout << "players shuffled...\n" << endl;
}

vector<Player *> GameEngine::getPlayersVect() {
    return plVec; //returns the vector containing player objects
}

void GameEngine::getMapList() {//helper method for loading list of maps from the directory in an ordered list
    int i = 0;
    string path = "../maps/";
    for (const auto &entry: fs::directory_iterator(path)) {
        if (entry.path().extension() == ".map") {
            std::cout << i + 1 << ": " << entry.path().filename() << endl;
            listOfFile.push_back(entry.path().filename().string());
            i++;
        }
    }
}

void GameEngine::setMap(Map *m) {
    map = m;
}

// Two main phases
void GameEngine::preStartup() {
    // loadmap <filename> to select map from list of map loaded
    //if (command=='loadmap') -> do this
    //GameEngine engine;
    int mapNum;
    string path = "../maps/";
    string mName;
    string fpath;

    MapLoader *mapLoader = new MapLoader();
    cout << "Initiating map loading stage: \n" << endl;
    getMapList();
    while (true) {
        cout << "\n Enter the number of the desired map: \n" << endl;
        cin >> mapNum;
        while (mapNum > listOfFile.size() || !(cin >> mapNum)) {
            cin.clear();
            cin.ignore(1000, '\n');
            if (!isdigit(mapNum)) {
                cout << "Wrong input. Try with a valid number! \n" << endl;
                continue;//breaking here if we input wrong number on the first try, doesnt work as intended even when entering correct number on 2nd try
            } else
                break;
        }
        mName = listOfFile[mapNum - 1];
        fpath = path.append(mName);
        Map x1 = *mapLoader->loadMap(fpath);
        Map *map1 = new Map(x1);
        map1->validate();// validates map
        map1->showLoadedMap();
        setMap(map1);
        break;
    }
    // addplayer loop
    //if(command==addplayer)-> do this
    while (true) {
//            string playerNameInput;
//            cout << "Enter player name: \n" << endl;
//            cin >> playerNameInput;
        cout << "Enter the number of players (between 2-6): \n" << endl;
        cin >> numberOfPlayers;
        setNumOfPlayers(numberOfPlayers);
        if (getNumOfPlayers() < 2 || getNumOfPlayers() > 6) {
            cin.clear();
            cin.ignore(1000, '\n');
            std::cout << "Invalid number of players. Please enter between 2-6 players. \n" << endl;
        } else {
            cout << "you have entered: " << getNumOfPlayers() << " players. Proceeding to next step....\n" << endl;
            break;
        }
    }
    //creating players based on given input (assigns army, hand, etc) and pushes the info into the player vector
    string playerName;
    for (int i = 0; i < getNumOfPlayers(); i++) {
        Player *p = new Player();
        Deck *cardDeck = new Deck();
        Hand *plCard = new Hand(cardDeck);
        cout << "enter name for player " << i + 1 << "....\n" << endl;
        cin >> playerName;
        p->setPlName(playerName);
        p->setCards(plCard);
        p->setPlArmies(5);
        cout << *p << "Number of Armies: " << p->getPlArmies() << endl;
        cout << "Cards in players hand: " << p->getHand() << endl;
        plVec.push_back(p);
        cout << "-------------------\n" << endl;
    }
    // gamestart ->
    /** 
         * - distribute territories of map between players
         * - determine order of play of players
         * - initially: give 50 armies to the players (50 between them? or 50 each?)
         * - each player draw 2 cards with deck.draw(2)
         * - go to play phase
         */

}

//startupPhase methods
StartupPhase::StartupPhase() {
    eng = new GameEngine();
}

StartupPhase::StartupPhase(const StartupPhase &sp) {
    this->eng = sp.eng;
}

StartupPhase::~StartupPhase() {

}

void StartupPhase::operator=(const StartupPhase &sp) {
    eng = sp.eng;
}

ostream &operator<<(ostream &out, const StartupPhase &sp) {
    //out<<"\nGame Engine: "<<sp.eng<< endl;//to fix
    return out;
}

std::istream &operator>>(std::istream &in, const StartupPhase &sp) {
    //in>>sp.eng;
    return in;
}

void StartupPhase::setGameEng(GameEngine *en) {
    eng = en;
}

void StartupPhase::startup() {
    int b = 0;
    //randomizing players order
    vector<Player *> a = eng->getPlayersVect();
    cout << "Randomize player order: \n" << endl;
    eng->randPlVec();
    cout << "Current order of players after randomize: \n" << endl;
    for (Player *p: eng->getPlayersVect()) {
        cout << *p << "----" << endl;
    }

    //giving armies to players:
    cout << "Starting Army distribution for players: \n" << endl;
    for (int i = 0; i < eng->getNumOfPlayers(); i++) {
        eng->getPlayersVect()[i]->setPlArmies(50);
    }
    cout << "Players have received 50 army each! \n" << endl;
    for (Player *p1: a) {
        cout << "player " << p1->getName() << ": " << p1->getPlArmies() << endl;

    }

    //letting players draw 2 cards
//    for (int i = 0; i < a.size(); i++) {
//        Deck *d = new Deck();
//        Hand *h = new Hand();
//        a[i]->setCards(h);
//        Player *p2 = a[i];
//        cout << "Player " << p2->getName() << " :\n" << endl;
//        d->showDeck();
//        d->draw(*p2);
//        d->draw(*p2);
//        cout << "Player drew 2 cards!" << endl;//needs fix
//    }

    //territory assignment
    cout << "Distributing territories to the players: \n" << endl;
    Map *map = eng->getMap();
    for (vector<Territory *>::iterator it = map->territoryNodeList.begin(); it != map->territoryNodeList.end(); ++it) {
        cout << " "
             << (**it).getName();
    }
    if (!map->territoryNodeList.empty()) {
        shuffle(begin(map->territoryNodeList), end(map->territoryNodeList), default_random_engine());

        while (!map->territoryNodeList.empty()) {
            vector<Player *> players = eng->getPlayersVect();
            for (Player *p: players) {
                if (!map->territoryNodeList.empty()) {
                    vector<Territory *> territories;
                    territories.push_back(map->territoryNodeList.back());
                    p->setTerritories(territories);
                    map->territoryNodeList.pop_back();
                }
            }

        }
        //for displaying players with acquired territories
        for (Player *p: eng->getPlayersVect()) {
            cout << *p << endl;
        }
    } else {
        cout << "The map has loading problems" << endl;
    }

}


void GameEngine::mainGameLoop() {
    //3 phases
    bool noWin = true;

    // main game loop: 3 phases repeat until game is won by someone
    while (noWin) {
        /** Phases are performed in sequence:
         * 1- Reinforcement phase:
         * 2- Issueing Orders phase:
         * 3- Orders Execution phase:
         */
        reinforcementPhase(); // player do nothing: they receive reinforcements, depending on outcome from prev turns

        issueOrdersPhase(); // players issue order and place them in list. This happens in round robin (switch between players)
        // Using play order determined in startupPhase, switch between player's turn . In actual game, this happens in parallel usign multiprocessing

        executeOrdersPhase(); // After both player have finished

        // win condition: one player own every territory in map
        noWin = checkWinCondition();
    }
}
