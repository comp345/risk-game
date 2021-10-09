#include <iostream>
#include <vector>
#include <string>
#include "GameEngine.h"
//using namespace GameEngineSpace;

GameEngine::GameEngine()
{
    // Initialize Engine level variables or env variables..
    command = "";
    currentState = "start";
    currentPlayers = 0;
    // StartupPhase::gameState['start'] = 0;
    // gameState['loadmap'] = 1;
    // gameState['validatemap'] = 2;
    // gameState['addplayer'] = 3;

    startUpLoop();
    cout << "Got to the consutrcture\n";
    // //LoadMap should return a Map OBJ (currently has to be a string to test)
    // string loadMap(string filePath);
    // // Need to pass a map
    // bool validatemap(Map myMap);
    // // Need to pass some players
}

// Replace with Map function from other parts when ready
string GameEngine::loadMap(string myMap)
{
    //Assumption that the map is loaded in project directory 

    return "success";
}

// We can use something like this on next iteration to automate the startup process
void GameEngine::startUpLoop() 
{
    cout << "Welcome to Warzone. Terminal style!\n";
    cout << "============================================\n";
    cout << "To start playing, enter loadmap\n";
    cin >> userInput;
    mapPath = loadMap(userInput);
    cout << "To validate map enter: validatemap\n";
    cin >> userInput;
    //validateMap();
    cout << "To add players enter: addplayer\n";
    cin >> userInput;
    cout << "Startup Phase complete. Starting the game...\n";
    //validateMap() - auto
    //playerAdd() - manual entry
    //changeState() - enter gameloop
};


bool GameEngine::addPlayer(Players currentPlayers)
{
    return true;
};

bool GameEngine::validateMap(Map myMap)
{
    return true;
};

string GameEngine::mapUserInputToCommand(string input)
{
    return "mapping";
};

void GameEngine::gameLoop()
{
    cout << "============================================\n";
    cout << "To start assigning countries, enter loadmap\n";
    for(int i = 0; i < currentPlayers; i++)
    {
        assignCountries()
    }

    
};