#include <any>
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "PlayerStrategies.h"
#include "Player.h"

using namespace std;

extern void riskGameDriver(string filename = ""); // driver for A2 P3

/* ***************************************** */
/*  A3 Part 1: Tools to test the strategies  */ // Do not forget to comment out or set these values to false
/* ***************************************** */ // when testing the tournament mode

bool testingStrategyMode = false; // if set to false, players will run with Normal strategy (from A2)

bool stopAfterEachTurn = true;

/* Comment out the combination of strategies to test
    1) Cheater and Normal player -> show the Cheater conquer everything in his way
    2) Benevolent players (2) -> show that 2 Benevolent players are in a permanent stalemate
    3) Neutral player and Normal -> show the Neutral player turning aggressive upon attack
    4) Aggressive player and Benevolent player -> show Aggressive player prioritizing strong territories (own and enemy)
    5) Human player and Benevolent player
*/
PlayerStrategy *arrayOfStrategies[2] = {new CheaterPlayerStrategy(new Player), new NormalPlayerStrategy(new Player)};
// PlayerStrategy * arrayOfStrategies[2] = {new BenevolentPlayerStrategy(new Player), new BenevolentPlayerStrategy(new Player)};
// PlayerStrategy * arrayOfStrategies[2] = {new NeutralPlayerStrategy(new Player), new NormalPlayerStrategy(new Player)};
// PlayerStrategy * arrayOfStrategies[2] = {new AggressivePlayerStrategy(new Player), new BenevolentPlayerStrategy(new Player)};
// PlayerStrategy * arrayOfStrategies[2] = {new HumanPlayerStrategy(new Player), new BenevolentPlayerStrategy(new Player)};

/* To test the tournament mode, just comment out/set to false ^ and input the command (or use fileadapter) */

int main(int, char **)
{
    /* *************************************** */
    /*          A2 P3 : Main Game play         */
    /* *************************************** */

    //    riskGameDriver("../debug.txt");
    //    riskGameDriver();

    /* *************************************** */
    /*       A3 P1 : Strategies driver         */
    /* *************************************** */

    // riskGameDriver("../strategy_driver_startup.txt"); // Auto run with file adapter
    

    /* *************************************** */
    /*         A3 P2 : Tournament mo  de       */
    /* *************************************** */

     riskGameDriver("../debug.txt");
}
