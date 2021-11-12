#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "GameEngine2.h"
#include "Map.h"

namespace fs= filesystem;
using namespace A2;

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
    transitions = vector<Transition *>(s.transitions); // Using vector copy constructor! Works, demonstration in testGameEngine
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
    nextState = nullptr;
}
Transition::Transition(string name)
{
    nameTransition = name;
    nextState = nullptr;
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
    this->nextState = new State(*(t.nextState));
    return *this;
}

// Creates the finite state machine that contains states and transitions
// The GameEngine object has access to the current state with getCurrentState(), as well
// as the valid transitions from that state with getCurrentPossibleTransitions()
GameEngine::GameEngine()
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
    Transition *assigncountriesTransition = new Transition("assigncountries", assignreinforcementState);
    Transition *issueorderTransition = new Transition("issueorder", issueordersState);
    Transition *endissueordersTransition = new Transition("endissueorders", executeordersState);
    Transition *execorderTransition = new Transition("execorder", executeordersState);
    Transition *endexecordersTransition = new Transition("endexecorders", assignreinforcementState);
    Transition *winTransition = new Transition("win", winState);
    Transition *playTransition = new Transition("play", startState);
    Transition *endTransition = new Transition("end", finalState);

    // Add transition to collection of transitions
    transitions = vector<Transition *>();
    transitions.push_back(loadmapTransition);
    transitions.push_back(validatemapTransition);
    transitions.push_back(addplayerTransition);
    transitions.push_back(assigncountriesTransition);
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
    playersaddedState->addTransition(assigncountriesTransition);
    assignreinforcementState->addTransition(issueorderTransition);
    issueordersState->addTransition(issueorderTransition);
    issueordersState->addTransition(endissueordersTransition);
    executeordersState->addTransition(execorderTransition);
    executeordersState->addTransition(endexecordersTransition);
    executeordersState->addTransition(winTransition);
    winState->addTransition(playTransition);
    winState->addTransition(endTransition);
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

// Only check if command is valid. Does NOT act upon the command, even if it is valid.
bool GameEngine::validateCommand(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            return true;
        }
    }
    return false;
}

// Check if command is valid. If it is, updates the state. Return true if command was valid, false if else.
// The success and error messages are not implemented, to allow flexible implementation in differents parts of A2.
bool GameEngine::doTransition(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            currentState = currentState->transitions.at(i)->nextState;
            return true;
        }
    }
    return false;
}

// Game play implementation for A1.
// TODO: Will need to divide game flow into StartUpPhase(), GameLoopPhase(), etc. for A2
void GameEngine::testGameEngine()
{
    GameEngine engine;
    cout << "Welcome to WarZone!" << endl;

    while (true)
    {
        string keyinput;

        cout << "Enter a valid command to progress in the game."
             << "(Enter x to quit or press any key when at final State)" << endl;

        cin >> keyinput;
        if (keyinput == "x" or engine.getCurrentStateName() == "final")
            break;
        else
        {
            cout << "\n***\n"
                 << endl;

            // Acting on the command. The function doTransition internally validates the command.
            // Returns true if command was valid, in order to display correct message.
            // TODO: switch statement to have different message for each state
            bool isCommandValid = engine.doTransition(keyinput);

            if (isCommandValid)
            {
                cout << "Valid command. Current state is: " << engine.getCurrentStateName() << endl;
            }
            else
            {
                cout << "Invalid command. Replay current state: " << engine.getCurrentStateName() << endl;
            }
        }
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
bool checkWinCondition()
{
    // Check if there is a player who wons every territory in map
    return false;
}
void GameEngine::reinforcementPhase()
{}
void GameEngine::issueOrdersPhase()
{}
void GameEngine::executeOrdersPhase()
{}
void GameEngine::getNumOfPlayers() {
    return numberOfPlayers;
}
//helper method for loading list of maps from the directory in an ordered list
void GameEngine::getMapList(){
    int i=0;
    string path= "../maps/";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".map") {
            std::cout << i+1  << ": " << entry.path().filename() << endl;
            listOfFile.push_back(entry.path().filename().string());
            i++;
        }
    }

    }
// Two main phases
void GameEngine::startupPhase()
{
    // loadmap <filename> to select map from list of map loaded

    //if (command=='loadmap') -> do this
    GameEngine engine;
    int mapNum;
    string path="../maps/";
    string mName;
    string fpath;

    MapLoader *mapLoader= new MapLoader();
        cout <<"Initiating map loading stage: \n"<<endl;
        getMapList();

        while(true){
            cout<<"\n Enter the number of the desired map: \n"<<endl;
            //cin>>mapNum;
            while(mapNum>listOfFile.size()||!(cin>>mapNum)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                if (!isdigit(mapNum)) {
                    cout << "Wrong input. Try with a valid number! \n" << endl;
                    continue;
                }
            }
                mName=listOfFile[mapNum-1];
                fpath=path.append(mName);
                Map x1 = *mapLoader->loadMap(fpath);
                Map *map1= new Map(x1);
                map1->validate();// validates map
            break;
        }
    // addplayer loop
        //if(command==addplayer)-> do this
        while(true) {
            string playerNameInput;
            cout << "Enter player name: \n" << endl;
            cin >> playerNameInput;
            cout << "Enter the number of players (between 2-5): \n" << endl;
            cin >> numberOfPlayers;
            if (numberOfPlayers < 2 || numberOfPlayers > 5) {
                cin.clear();
                cin.ignore(1000, '\n');
                std::cout << "Invalid number of players. Please enter between 2-5 players. \n" << endl;
            } else{
                break;
            }
        }

        //create a vector of players and assign the playernumInput as the vector size

    // gamestart ->
    /** 
         * - distribute territories of map between players
         * - determine order of play of players
         * - initially: give 50 armies to the players (50 between them? or 50 each?)
         * - each player draw 2 cards with deck.draw(2)
         * - go to play phase
         */

}

void GameEngine::mainGameLoop()
{
    //3 phases
    bool noWin = true;

    // main game loop: 3 phases repeat until game is won by someone
    while (noWin)
    {
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
