#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Orders.hpp"
#include "Card.h"
#include "GameEngine2.h"

using namespace std;

int main(int, char **)
{
    GameEngine *engine= new GameEngine();
    StartupPhase sp;
    //engine.testGameEngine();
    engine->preStartup();
    sp.setGameEng(engine);
    sp.startup();
    return 0;
}
