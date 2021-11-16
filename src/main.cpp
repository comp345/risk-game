#include <iostream>
#include <string.h>
#include "Player.h"
#include "Map.h"
#include "Orders.hpp"
#include "Card.h"
#include "GameEngine2.h"

using namespace std;


std::string checkCliArgs(int argNumber,char *argv[])
{
    string fileName = "";
    
    for (int i = 0; i < argNumber; ++i) 
    {
        // Not that nice but assumes argv[2] is a file 
        if(argv[1] && (strcmp(argv[i],"-f")) && argv[2])
        {
            fileName = argv[2]; 
        }
    }
    return fileName;
}

void testCommandProcessor(int argc, char *argv[])
{
    string fileName = checkCliArgs(argc, argv);
    if(fileName.empty())
    {
        GameEngine engine;
        engine.testGameEngine();
    }
    else
    {
        GameEngine engine{fileName};
        engine.testGameEngine();
    }
}
int main(int argc, char *argv[], char **)
{
    testCommandProcessor(argc, argv);
    return 0;
}
