#include "GameEngine.h";
#include <iostream>
#include <vector>
#include <string>
using namespace GameEngine;

StartupPhase::StartupPhase(){
    // Initialize my variables
    currentState = "start";
    gameStates {
        {'start', 0},
        {'loadmap', 1}
        {'validatemap', 2}
        {'addplayer,' 3}
    }
    void loadMap(string filePath);
    // Need to pass a map
    bool mapValidated(Map myMap);
    // Need to pass some players
}

// We can use something like this on next iteration to automate the startup process
void StartupPhase::StartupPhaseTemplate() 
{
    //loadMap() - set default location
    //validateMap() - auto
    //playerAdd() - manual entry
    //changeState() - enter gameloop
}

void loadMap(string filePath)
{

}

bool PlayersAdded(Players currentPlayers)
{

}

bool mapValidated(Map myMap)
{

}

void mapUserInputToCommand(string input)
{

}