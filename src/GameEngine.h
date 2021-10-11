#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;


    void testEngineLink();


    enum STARTUP_STATES {
        start,
        loadmap,
        validateMap,
        addplayer,
        assigncountries
    };

    enum GAME_STATES {
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
        public: 
            Map(){}
    };

    class Player {
        public: 
            Player(){}
    };

    class GameEngine 
    {

    private:
        string command;
       // Input attribyte
        int intInput;
        string stringInput;
        vector<string> maps;
        //LoadMap should return a Map OBJ (currently has to be a string to test)
        string loadMap(string filePath);
        int numPlayers;
        //vector<Player> currentPlayers;
        vector<int> currentPlayers;
        // Need to pass a map
        bool validateMap(string myMap);
        // Need to pass some players
        vector<int> addPlayers(int numberOfPlayers);
        //vector<Player> addPlayer(int numberOfPlayers);
        void assignReinformentPhase();
        void issueOrderPhase();
        void executeOrderPhase();
        void gameLoop();
    public:
        string currentState;
        typedef std::map<STARTUP_STATES, std::string> startUpStateMap;
        typedef std::map<GAME_STATES, std::string> gamesStateMap;
        map<string, int>::iterator checker;
        string mapPath;
        GameEngine &operator=(const GameEngine &o);
        friend std::ostream &operator<<(std::ostream &out, const GameEngine &o);
        friend std::istream &operator>>(std::istream &in, GameEngine& o);
        GameEngine();
        void startUpLoop();
        void changeState();
        void testEngineDriver();
        void setupMaps();

    };
