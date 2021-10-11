#include "GameEngine.h"
#include <iostream>
#include <vector>

void testEngineLink() 
{
    cout << "Successfully linked engine.cpp and engine.hpp to main\n";
    GameEngine* tester = new GameEngine();
}