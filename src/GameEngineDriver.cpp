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