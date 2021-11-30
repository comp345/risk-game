#include <iostream>
#include "GameEngine.h"

using namespace std;

int main(int, char **)
{
    GameEngine *engine= new GameEngine();
    engine->preStartup();
}
