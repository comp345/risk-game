#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "orders.hpp"
#include <map>
using namespace std;


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
    class GameEngine 
    {

    private:
        
        string command;
       // Input attribyte
        string userInput;
        //LoadMap should return a Map OBJ (currently has to be a string to test)
        string loadMap(string filePath);
        int currentPlayers;
        // Need to pass a map
        bool validateMap(Map myMap);
        // Need to pass some players
        bool addPlayer(Players currentPlayers);
        void assignReinformentPhase();
        void issueOrderPhase();
        void executeOrderPhase();
        void gameLoop();
    public:
        string currentState;
        map<string, int> gameState;
        map<string, int>::iterator checker;
        string mapPath;
        GameEngine &operator=(const GameEngine &o);
        friend std::ostream &operator<<(std::ostream &out, const GameEngine &o);
        friend std::istream &operator>>(std::istream &in, GameEngine& o);
        GameEngine();
        void startUpLoop();
        string mapUserInputToCommand(string input);
        void changeState();
        void testEngineDriver();
    };
