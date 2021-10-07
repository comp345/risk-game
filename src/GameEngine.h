#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "orders.hpp"
#include <map>
using namespace std;

namespace GameEngine
{
    // Temp adjustment until other classes are ready
    class Map {

    };
    // Temp adjustment until other classes are ready
    class Players {

    };

    class StartupPhase
    {   
    private:
       // Input attribyte
        string userInput;
        void loadMap(string filePath);
        // Need to pass a map
        bool mapValidated(Map myMap);
        // Need to pass some players
        bool PlayersAdded(Players currentPlayers);


    public:
        string currentState;
        map<string, int> gameStates;
        map<string, int>::iterator checker;
        StartupPhase();
        void StartupPhaseTemplate();
        bool mapUserInputToCommand(string input);
        void changeState(int phase)
    };

    class GameLoopPhase
    {
    private: 
        void assignReinformentPhase();
        void issueOrderPhase();
        void executeOrderPhase();
        void gameLoopTemplate();
    public:
        map<string, int> gameState;
        map<string, int>::iterator checker;
    };

};
