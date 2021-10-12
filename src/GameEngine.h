#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;


    void gameLoopEngineDriver();

    enum GAME_STATES {
        start,
        loadmap,
        validateMap,
        addplayer,
        assigncountries,
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
        int command;
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
        void resetGame();
        void assignReinformentPhase();
        void assignCountries();
        void issueOrderPhase();
        void endissueorders();
        void executeOrderPhase();
        void endexecorders();
        void win();
        void execPhase(string userMessage, int state, void (GameEngine::*passedFunc)());
    public:
        int currentState;
        int numOfMaps;
        typedef std::map<std::string, GAME_STATES> stateMap;
        stateMap startUpMap;
        stateMap gameStateMap;
        string mapPath;
        int mapUserInputToCommand(string &input, int &currentState, stateMap stateMap);
        GameEngine &operator=(const GameEngine &o);
        friend std::ostream &operator<<(std::ostream &out, const GameEngine &o);
        friend std::istream &operator>>(std::istream &in, GameEngine& o);
        GameEngine();
        ~GameEngine();
        void run();
        void startUpLoop();
        void gameLoop();
        void setupMaps();


    // inline bool operator <(const STARTUP_STATES left, const STARTUP_STATES right)
    // {
    //     return static_cast<int>(left) < static_cast<int>(right);
    // }

    // inline bool operator >(const STARTUP_STATES left, const STARTUP_STATES right)
    // {
    //     return static_cast<int>(left) > static_cast<int>(right);
    // }
    };
