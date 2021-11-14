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
        if(argv[1] && (strcmp(argv[i],"-f")) && argv[2])
        {
            fileName = argv[2]; 
        }
    }
    //cout <<"argv -> "<<fileName << "\n";
    return fileName;
}

int main(int argc, char *argv[], char **)
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
    return 0;
}
