#include <iostream>
#include "GameEngine.h"


using namespace std;

int main(int, char **)
{
    //cout << "Hello, world!\n";
    // Test if orders.hpp and orders.cpp are properly linked/compiled
    //testEngineLink();

    gameLoopEngineDriver();
    cout << "============================================\n";
    cout << "Hello, world!\n";

    return 0;
}
