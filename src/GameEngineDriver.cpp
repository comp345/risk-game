#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <string>
//using namespace GameEngineSpace;

void gameLoopEngineDriver() 
{
    GameEngine* engine = new GameEngine();
    engine->run();
}
    cout << "Successfully linked engine.cpp and engine.hpp to main\n";
    GameEngine* tester = new GameEngine();
}

// int main() 
// {
//     gameLoopEngineDriver();
// }
