#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "GameEngine.h"

//using namespace GameEngineSpace;


GameEngine::GameEngine()
{
    // Initialize Engine level variables or env variables..
    command = 0;
    currentState = GAME_STATES::start;
    numPlayers = 0;
    numOfMaps = 0;
    startUpLoop();
    gameLoop();
}

// We can use something like this on next iteration to automate the startup process
void GameEngine::startUpLoop() 
{
    stateMap startUpMap = {
        { "loadmap", GAME_STATES::loadmap },
        { "validatemap", GAME_STATES::validateMap },
        { "addplayer", GAME_STATES::addplayer },
        { "assigncountries", GAME_STATES::assigncountries }
    };

        cout << "Welcome to Warzone. Terminal style!"<< std::endl;
        cout << "============================================"<< std::endl;
    

    while(true)
    {
        currentState = GAME_STATES::loadmap;
        // I dunno how to fix valid -> invalid input... Cant reset the cin
        cin.clear();
        numOfMaps = -1;
        cout << "To start playing, enter number of maps to load: "<< std::endl;
        cin >> numOfMaps;

        if(!cin)
        {
            cout << "Invalid Input! Need to enter a number..."<< std::endl;;
            break;
        }
        else
        {
            for(int i = 0; i < numOfMaps; i++)
            {
                //Same issue as reseting...
                stringInput = "";
                command = 0;
                cin.clear();
                cout << "Load your maps with loadmap"<< std::endl;
                cin >> stringInput;
                command = mapUserInputToCommand(stringInput, currentState, startUpMap);
                if(command == -1)
                {
                    std::cout << "Forcing a restart on current iteration: " + to_string(i) << std::endl;
                    i--;
                }
            }
            if(command == currentState)
            {
                setupMaps();
                currentState = GAME_STATES::validateMap;
                break;
            }
        }
    }


    while(true)
    {
        cout << "To start validating maps enter: validatemap"<< std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, startUpMap);
        if(command == currentState)
        {
            validateMap("testMap");
            currentState = GAME_STATES::addplayer;
            break;
        }
        else
        {
            cout << "Not valid entry...."<< std::endl;
            continue;
        }
    }

    while(true)
    {
        currentState = GAME_STATES::addplayer;
        cin.clear();
        cout << "Enter number of players: "<< std::endl;
        cin >> numPlayers;

        if(!cin)
        {
            cout << "Invalid Input! Need to enter a number..."<< std::endl;
            break;
        }
        else
        {
            for(int i = 0; i < numPlayers; i++)
            {
                //create new players + more logic..
                //AddPlayer Functions...
                cout << "Creating player: "+ to_string(i+1) + ".... Done."<< std::endl;
            }
            currentState = GAME_STATES::assigncountries;
            cin.clear();
            cout << "Assign countries to player by entering: assigncountries"<< std::endl;
            cin >> stringInput;
            command = mapUserInputToCommand(stringInput, currentState, startUpMap);
            if(command == currentState)
            {
            for(int i = 0; i < numPlayers; i++)
                {
                    //assigning territories + more logic...
                    //Assign Functions...
                    cout << "Assign countries for player:"+ to_string(i+1) + ".... Done\n" << std::endl;
                }
                break;
            }
            else if(command == -1)
            {
                cout << "Not valid command..." << std::endl;
                continue;
            }
        }
    }

    cout << "Startup Phase complete. Starting the game...\r"<< std::endl;


        // switch(command)
        // {
        //     // case STARTUP_STATES::loadmap:
        //     // cout << "Loading maps..."<< std::endl;;
        //     // setupMaps();
        //     cout << "To validate enter: validatemap"<< std::endl;;
        //     cin >> stringInput;
        //     command = mapUserInputToCommand(stringInput, currentState, state2);
        //     case STARTUP_STATES::validateMap:
        //     cout << "Validating maps..."<< std::endl;;
        //     validateMap("SomeMap");
        //     cout << "To start adding players enter: addplayer"<< std::endl;;
        //     cin >> stringInput;
        //     command = mapUserInputToCommand(stringInput, currentState, state2);
        //     case STARTUP_STATES::addplayer:
        //     cout << "Add number of players: "<< std::endl;;
        //     cin >> intInput;
        //     addPlayers(intInput);
        //     default:
        //     cout << "Invalid Input...\r"<< std::endl;;
        //     cin >> stringInput;
        //     command = mapUserInputToCommand(stringInput, currentState, state2);
        // }
};

// Replace with Map function from other parts when ready
string GameEngine::loadMap(string mapName)
{
    currentState = GAME_STATES::loadmap;
    cout << "Loading Maps....!"<< std::endl;;
    cout << "============================================"<< std::endl;
    for(int i = 0; i < numOfMaps; i++)
    {   
        cout << std::string("Added map #: ") + to_string(i +1) << std::endl;
    }
    //Assumption that the map is loaded in project directory 
    return "mapLoaded";
}


void GameEngine::setupMaps()
{
    // Will use this after understanding how all maps get loaded.
    mapPath = loadMap("someMap");
    //Update state after done loading maps
    //currentState = STARTUP_STATES::validateMap;
};

bool GameEngine::validateMap(string myMap)
{
    cout << "Map validated!" <<std::endl;
    currentState = GAME_STATES::assigncountries;
    return true;
};

vector<int> GameEngine::addPlayers(int numberOfPlayers)
{
    currentState = GAME_STATES::addplayer;
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

void GameEngine::assignCountries()
{
    cout << "Assigning Countries....";
}

void GameEngine::nextPhase(int state, function<void (int)> func) {
    func(state);
}

int GameEngine::mapUserInputToCommand(string &input, int &currentState, stateMap stateMap)
{
    cout << "Passed values: "+input+" - input string"<< std::endl;;
    cout << "Passed values: "+to_string(currentState)+" - current state "<< std::endl;;
    
    for (auto itr = stateMap.find(input); itr != stateMap.end(); itr++) 
    {
        cout << itr->first << '\t' << itr->second << '\n';

        intInput = itr->second;
        break;
    }
    
    if(currentState == intInput)
    {
        cout << "VALID game state! "+ input+" is GUCCI.\r"<< std::endl;;
        return currentState;
    }
    else
    {
        cout << "Invalid game state! "+ input+" is incorrect. \r"<< std::endl;;
        return -1;
    }
};

void GameEngine::executeOrderPhase()
{

}
void GameEngine::issueOrderPhase()
{

}
void GameEngine::endissueorders()
{

}

void GameEngine::gameLoop()
{
    cout << "============================================"<< std::endl;;
    cout << "Starting game.... "<< std::endl;;


    stateMap gameStateMap = {
        { "issueorder" ,GAME_STATES::issueorder },
        { "endissueorders", GAME_STATES::endissueorders },
        { "execorder", GAME_STATES::execorder},
        { "endexecorders", GAME_STATES::endexecorders },
        { "win", GAME_STATES::win},
        { "play", GAME_STATES::play},
        { "end", GAME_STATES::end}
    };

while(true)
{

    currentState = GAME_STATES::issueorder;

    while(true)
    {
        cin.clear();
        cout << "Issue orders by entering: issueorder"<< std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == currentState)
        {
            issueOrderPhase();
            currentState = GAME_STATES::endissueorders;
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }

    }

    while(true)
    {
        cin.clear();
        cout << "End Issue orders by entering: endissueorders"<< std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == currentState)
        {
            endissueorders();
            currentState = GAME_STATES::execorder;
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }
    }

    while(true)
    {
        cin.clear();
        cout << "End exec orders by entering: execorders"<< std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == currentState)
        {
            executeOrderPhase();
            currentState = GAME_STATES::endexecorders;
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }

    }

    while(true)
    {
        cin.clear();
        cout << "End exec orders by entering: endexecorders"<< std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == currentState)
        {
            executeOrderPhase();
            currentState = GAME_STATES::endexecorders;
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }
        continue;
    }
    break;
}


    // switch((int) userInput)
    // {
    //     case GAME_STATES::issueorder:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::endissueorders:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::execorder:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::endexecorders:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::win:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::play:
    //     cout << "Loading..."<< std::endl;;
    //     case GAME_STATES::end:
    //     cout << "Loading..."<< std::endl;;
    // }

    
};