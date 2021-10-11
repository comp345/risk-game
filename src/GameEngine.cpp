#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "GameEngine.h"

//using namespace GameEngineSpace;

namespace fs = filesystem;

GameEngine::GameEngine()
{
    // Initialize Engine level variables or env variables..
    command = "";
    currentState = STARTUP_STATES::start;
    numPlayers = 0;
    startUpLoop();
    
}

// Replace with Map function from other parts when ready
string GameEngine::loadMap(string mapName)
{
    currentState = STARTUP_STATES::loadmap;
    cout << "Loading Maps....!\n";
    cout << "============================================\n";
    string playerNum = "";
    for(int i = 0; i < 5; i++)
    {   
        cout << std::string("Added map #: ") + to_string(i) + std::string("\n");
    }
    //Assumption that the map is loaded in project directory 
    return "mapLoaded";
}

// We can use something like this on next iteration to automate the startup process
void GameEngine::startUpLoop() 
{
    bool startingUp = true;

    startUpStateMap state = {
        { STARTUP_STATES::loadmap, "loadmap" },
        { STARTUP_STATES::validateMap, "validatemap"},
        { STARTUP_STATES::addplayer, "addplayer"},
        { STARTUP_STATES::assigncountries, "assigncountries"}
    };

    while(startingUp)
    {
        cout << "Welcome to Warzone. Terminal style!\n";
        cout << "============================================\n";
        //call loadmap on each input Map
        cout << "To start playing, enter which maps you want to load\n";
        currentState = STARTUP_STATES::loadmap;
        cin >> stringInput;


        switch(intInput)
        {
            case STARTUP_STATES::loadmap:
            cout << "Loading...\n";
            setupMaps();
            break;
            case STARTUP_STATES::validateMap:
            cout << "Loading...\n";
            break;
            case STARTUP_STATES::addplayer:
            cout << "Add number of players: \n";
            cin >> intInput;
            addPlayers(intInput);
            break;
        }
        cout << "Startup Phase complete. Starting the game...\n";
        startingUp = false;
    }

};

void GameEngine::setupMaps()
{
    mapPath = loadMap(stringInput);
    cout << "Validating map...\n";
    cin >> stringInput;
    validateMap(mapPath);
};


vector<int> GameEngine::addPlayers(int numberOfPlayers)
{
    currentState = STARTUP_STATES::addplayer;
    currentPlayers.resize(numberOfPlayers);
    for(int i=0; i < numberOfPlayers; i++)
    {
        currentPlayers.push_back(i);
    }
    return currentPlayers;
};

// Adding a Player version
// vector<Player> GameEngine::addPlayers(int numberOfPlayers)
// {

//     currentState = STATES::addplayer;
//     currentPlayers.resize(numberOfPlayers);
//     for(int i=0; i < numberOfPlayers; i++)
//     {
//         currentPlayers.push_back(i);
//     }
//     return currentPlayers;
// };

void assignCountries(vector<int> players)
{

}

bool GameEngine::validateMap(string myMap)
{
    currentState = STARTUP_STATES::validateMap;
    return true;
};

// string GameEngine::mapUserInputToCommand(string input)
// {
//     return "mapping";
// };

void GameEngine::gameLoop()
{
    cout << "============================================\n";
    cout << "To start assigning countries, enter loadmap\n";
    // for(int i = 0; i < currentPlayers; i++)
    // {
    //     assignCountries()
    // }

        gamesStateMap state = {
        { GAME_STATES::issueorder, "issueorder" },
        { GAME_STATES::endissueorders, "endissueorders"},
        { GAME_STATES::execorder, "execorder"},
        { GAME_STATES::endexecorders, "endexecorders"},
        { GAME_STATES::win, "win"},
        { GAME_STATES::play, "play"},
        { GAME_STATES::end, "end"},
    };


    // switch((int) userInput)
    // {
    //     case GAME_STATES::issueorder:
    //     cout << "Loading...\n";
    //     case GAME_STATES::endissueorders:
    //     cout << "Loading...\n";
    //     case GAME_STATES::execorder:
    //     cout << "Loading...\n";
    //     case GAME_STATES::endexecorders:
    //     cout << "Loading...\n";
    //     case GAME_STATES::win:
    //     cout << "Loading...\n";
    //     case GAME_STATES::play:
    //     cout << "Loading...\n";
    //     case GAME_STATES::end:
    //     cout << "Loading...\n";
    // }

    
};