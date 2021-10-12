#include <iostream>
#include <vector>
#include <string>
<<<<<<< HEAD
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

    stateMap startUpMap = {
        { "loadmap", GAME_STATES::loadmap },
        { "validatemap", GAME_STATES::validateMap },
        { "addplayer", GAME_STATES::addplayer },
        { "assigncountries", GAME_STATES::assigncountries }
    };

    stateMap gameStateMap = {
        { "issueorder" ,GAME_STATES::issueorder },
        { "endissueorders", GAME_STATES::endissueorders },
        { "execorder", GAME_STATES::execorder},
        { "endexecorders", GAME_STATES::endexecorders },
        { "win", GAME_STATES::win},
        { "play", GAME_STATES::play},
        { "end", GAME_STATES::end}
    };
}

GameEngine::~GameEngine()
{
    // To update when integrating....
    command = 0;
    currentState = GAME_STATES::start;
    numPlayers = 0;
    numOfMaps = 0;
    startUpMap.clear();
    gameStateMap.clear();
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
                // cout << "command value on entry:" + to_string(command) << endl;
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

void GameEngine::execPhase(string userMessage, int currentState, void (GameEngine::*passedFunc)()) {

    while(true)
    {
        cin.clear();
        cout << userMessage << std::endl;
        cin >> stringInput;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == currentState)
        {
            (this->*passedFunc)();
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }
    }
}

int GameEngine::mapUserInputToCommand(string &input, int &currentState, stateMap stateMap)
{    
    for (auto itr = stateMap.find(input); itr != stateMap.end(); itr++) 
    {
       // cout << itr->first << '\t' << itr->second << '\n';

        intInput = itr->second;
        break;
    }
    
    if(currentState == intInput)
    {  
        cout << "Command Executed.\r\n"<< std::endl;;
        return currentState;
    }
    else
    {
        cout << "Invalid game state! "+ input+" is incorrect. \r\n"<< std::endl;;
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

void GameEngine::endexecorders()
{

}   


void GameEngine::win()
{

}

void GameEngine::resetGame()
{
    run();
}

void GameEngine::run()
{
    while(true)
    {
        startUpLoop();
        gameLoop();
    }
}

void GameEngine::gameLoop()
{
    cout << "============================================\n"<< std::endl;;

    string issueOrderMessage = "Issue orders by entering: issueorder";
    string endissueOrderMessage ="End Issue orders by entering: endissueorders";
    string execOrderMessage = "Start executing orders by entering: execorders";
    string endExecOrderMessage = "End exec orders by entering: endexecorders";
    bool playing = true;

        stateMap gameStateMap = {
        { "issueorder" ,GAME_STATES::issueorder },
        { "endissueorders", GAME_STATES::endissueorders },
        { "execorder", GAME_STATES::execorder},
        { "endexecorders", GAME_STATES::endexecorders },
        { "win", GAME_STATES::win},
        { "play", GAME_STATES::play},
        { "end", GAME_STATES::end}
    };

while(playing)
{
    // execPhase(issueOrderMessage, currentState, &GameEngine::issueOrderPhase);

    // currentState = GAME_STATES::endissueorders;

    // execPhase(endissueOrderMessage, currentState, &GameEngine::endissueorders);

    // currentState = GAME_STATES::execorder;

    // execPhase(execOrderMessage, currentState, &GameEngine::executeOrderPhase);

    // currentState = GAME_STATES::endexecorders;

    // execPhase(endExecOrderMessage, currentState, &GameEngine::endexecorders);

    while(true)
    {
        currentState = GAME_STATES::issueorder;
        stringInput = "";
        cin.clear();
        cout << "Issue orders by entering: issueorder or end issuing orders with: endissueorders"<< std::endl;
        cin >> stringInput;
        if(stringInput == "endissueorders") {
        currentState = GAME_STATES::endissueorders;
        }
        command = 0;
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        //Replace this with switch
        if(command == GAME_STATES::issueorder)
        {
            issueOrderPhase();
            continue;
        }
        else if(command == GAME_STATES::endissueorders)
        {
            endissueorders();
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
        cout << "Execute orders by entering: execorders or End order execution with endexecorders. If you won enter: win"<< std::endl;
        cin >> stringInput;
        //Replace this with switch
        if(stringInput == "execorder") {
        currentState = GAME_STATES::execorder;
        }
        else if(stringInput == "endexecorders") {
        currentState = GAME_STATES::endexecorders;
        }
        else if(stringInput == "win") {
        currentState = GAME_STATES::win;
        }
        command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
        if(command == GAME_STATES::execorder)
        {
            executeOrderPhase();
            continue;
        }
        else if (command == GAME_STATES::endexecorders)
        {
            endexecorders();
            break;
        }
        else if (command == GAME_STATES::win)
        {
            win();
            playing = false;
            break;
        }
        else if(command == -1)
        {
            cout << "Not valid command..." << std::endl;
            continue;
        }
    }
}

    cin.clear();
    cout << "Restart another round with: play or end game with: end"<< std::endl;
    cin >> stringInput;
    //Replace this with switch
     if(stringInput == "play") {
        currentState = GAME_STATES::play;
    }
    else if(stringInput == "end") {
        currentState = GAME_STATES::end;
    }
    command = mapUserInputToCommand(stringInput, currentState, gameStateMap);
    if(command == GAME_STATES::play)
    {
        cout << "Restarting.... New game!\n"<< std::endl;
        resetGame();
    }
    else if (command == GAME_STATES::end)
    {
        cout << "Thanks for playing :) "<< std::endl;
        exit(0);
    }
};

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
=======
#include "GameEngine.h"
//using namespace GameEngineSpace;

GameEngine::GameEngine() {
    // Initialize Engine level variables or env variables..
    command = "";
    currentState = "start";
    numPlayers = 0;
    // StartupPhase::gameState['start'] = 0;
    // gameState['loadmap'] = 1;
    // gameState['validatemap'] = 2;
    // gameState['addplayer'] = 3;

    startUpLoop();
    cout << "Got to the constructor\n";
    // //LoadMap should return a Map OBJ (currently has to be a string to test)
    // string loadMap(string filePath);
    // // Need to pass a map
    // bool validatemap(Map myMap);
    // // Need to pass some players
}


// We can use something like this on next iteration to automate the startup process
void GameEngine::startUpLoop() {
    cout << "Welcome to Warzone. Terminal style!\n";
    cout << "============================================\n";
    cout << "To start playing, enter which maps you want to load\n";
    // cin >> userInput;
    // mapPath = loadMap(userInput);
    cout << "Validating map...\n";
    cin >> userInput;
    //validateMap();
    cout << "Add number of players: \n";
    cin >> userInput;
    addPlayer(stoi(userInput));
    cout << "Startup Phase complete. Starting the game...\n";
    //validateMap() - auto
    //playerAdd() - manual entry
    //changeState() - enter gameloop
}


vector<Player *> GameEngine::addPlayer(int numberOfPlayers) {
    currentState = STATES::addplayer;
    currentPlayers.resize(numberOfPlayers);
    for (int i = 0; i < numberOfPlayers; i++) {
        Player *player = new Player();
        currentPlayers.push_back(player);
    }
    return currentPlayers;
}

bool GameEngine::validateMap(Map myMap) {
    return true;
}

string GameEngine::mapUserInputToCommand(string input) {
    return "mapping";
}

void GameEngine::gameLoop() {
    cout << "============================================\n";
    cout << "To start assigning countries, enter loadmap\n";
    // for(int i = 0; i < currentPlayers; i++)
    // {
    //     assignCountries()
    // }
}
>>>>>>> origin/a1_finalOrders_toMergeBackTo_a1
