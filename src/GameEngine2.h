#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "CommandProcessor.h"

/* The states and transitions are stored in a linked list like structure */

// States are Nodes in the game flow

    class GameEngine : public ILoggable, public Subject
    {
        friend class State;
        friend class Transition;

    private:
        State *currentState; 
        State *processorStates;
        bool isFile;
        std::string fileName;
        std::vector<State *> states; // GameEngine maintains collection of all states
        std::vector<Transition *> transitions; // GameEngine maintains collection of all valid commands/transitions
        CommandProcessor *commandProcessor;
        FileCommandProcessorAdapter *fileAdapter;
    public:
        GameEngine();
        GameEngine(std::string fileName);

        // return name of current state
        std::string getCurrentStateName(); 
        
        // return names of possible commands in current state
        std::vector<std::string> getNextTransitions(); 
        
        // return state name if command is performed. TODO: throw exception if invalid command.
        std::string getNextStateName(std::string command); 

        // check if command is valid and updates current state accordingly
        bool doTransition(std::string command);

        // check if command is valid. no update.
        bool validateCommand(std::string command);

        // setup command processor responsibility transitions
        State* setupCommandProcessorStates();
        
        void testGameEngine();
        string stringToLog() override;

    /* A2 */

        // A2 Part 2
        void startupPhase();

        // A2 Part 3
        void mainGameLoop();
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();

    };

