#include <iostream>
#include "GameEngine.h"

using namespace std;

extern void riskGameDriver(); // driver for A2 P3

int main(int, char **)
{
    /* *************************************** */
    /*              A2 P2 : Startup            */
    /* *************************************** */
    GameEngine *engine= new GameEngine();
    engine->preStartup();

    /* *************************************** */
    /*          A2 P3 : Main Game play         */
    /* *************************************** */

    // riskGameDriver();



}
