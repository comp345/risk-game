#include <iostream>
#include <string>
#include <vector>
#include "GameEngine2.h"

using namespace std;

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
//    stateTracker = &startState;

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
    State *assignreinforcementState = new State("assignreinfgamorcement");
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

State* GameEngine::setupCommandProcessorStates()
{
    
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

// Check if command is valid. If it is, updates the state. Return true if command was valid, false if else.
// The success and error messages are not implemented, to allow flexible implementation in differents parts of A2.
bool GameEngine::doTransition(string command)
{
    // cout << "Ending up gettin gin the gameengine transtion " << std::endl;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        //cout << "AM I GETTIN GIN HTERE -  " << *currentState << std::endl;
        cout << "AM I GETTIN GIN HTERE2222 -  " << (currentState->transitions.at(i)->nameTransition) << std::endl;
        cout << "AM I GETTIN GIN HTERE2222 -  " << (command) << std::endl;
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            cout << "BEFORE Ending up gettin inside the ENGINE TRANSITION -  " << *currentState << std::endl;

            *currentState = *currentState->transitions.at(i)->nextState;
            cout << "AFTER Ending up gettin inside the ENGINE TRANSITION -  " << *currentState << std::endl;

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
            output = commandProcessor->getCommand(currentState);
            cout << "return output from processor: " << output->getCommandName() << std::endl;
            doTransition(output->getCommandName());            
            cout << "\n";
        
        }

    }
    else
        while(true)
        {
            output = fileAdapter->getCommand(currentState);
            cout << "return output from file: " << output->getCommandName() << std::endl;
            cout << "This is the current state: " << getCurrentStateName() << std::endl;
            //cout << "Boolean: " << (output->getCommandName() == getCurrentStateName()) << std::endl;
            doTransition(output->getCommandName());
            //break;
            if(output->getCommandName() == "gamestart")
            {
                //Start the gameloop
                
            }
            else if(output->getCommandName() == "quit")
                exit(0);
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

// Two main phases
void GameEngine::startupPhase()
{
    // loadmap <filename> to select map from list of map loaded

    // validate map

    // addplayer loop

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
