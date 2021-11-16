#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // need for rand() function
#include "GameEngine.h" // NEEDED
#include "Orders.h" // NEEDED
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Card.h"

using namespace std;
using namespace A2;

int main(int, char **)
{
//     srand(time(NULL));
//     /* A1 : GameEngine */
//     // GameEngine engine;
//     // engine.testGameEngine();

//     /* A2 : Part 4 */
//     // testOrdersA2();

//     /* A2 : Debugging operator= from Deploy and Player */
//     // testAssignmentOperator();

//     /* A2 : Debugging Constructor and assignment operator defined in Map of A1 */
//     // testA2Map();

//     /* A2 : Testing Deploy exec */
//     // testDeployExec();

//     /* A2 : Testing Advance exec */
//     // testAdvanceExec();

//     /* A2 : Testing AirLift exec */
//     // testAirliftExec();

    // /* A2 : Testing GameLoop */
    GameEngine::testGameEngine();

    return 0;
}
