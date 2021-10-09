#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "orders.hpp"
#include <map>
using namespace std;


namespace GameEngine 
{
    void testEngineLink();

    enum STATES {
        start,
        loadmap,
        validateMap,
        addplayer,
        assignCountries,
        issueorder,
        endissueorders,
        execorder,
        endexecorders,
        win,
        play,
        end
    };


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
        //LoadMap should return a Map OBJ (currently has to be a string to test)
        string loadMap(string filePath);
        int currentPlayers;
        // Need to pass a map
        bool validatemap(Map myMap);
        // Need to pass some players
        bool addplayer(Players currentPlayers);


    public:
        string currentState;
        map<string, int> gameState;
        map<string, int>::iterator checker;
        string mapPath;
        StartupPhase &operator=(const StartupPhase &o);
        friend std::ostream &operator<<(std::ostream &out, const StartupPhase &o);
        friend std::istream &operator>>(std::istream &in, StartupPhase& o);
        StartupPhase();
        void startUpLoop();
        bool mapUserInputToCommand(string input);
        void changeState();
        void testEngineLink();
        void testEngineDriver();
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


}