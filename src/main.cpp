#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // need for rand() function
#include "GameEngine2.h" // NEEDED
#include "Orders.h" // NEEDED

using namespace std;
using namespace A2;

int main(int, char **)
{
    srand(time(NULL));
    /* A1 : GameEngine */
    // GameEngine engine;
    // engine.testGameEngine();

    /* A2 : Part 4 */
    // testOrdersA2();

    /* A2 : Debugging operator= from Deploy and Player */
    // testAssignmentOperator();

    /* A2 : Debugging Constructor and assignment operator defined in Map of A1 */
    // testA2Map();

    /* A2 : Testing Deploy exec */
    // testDeployExec();

    /* A2 : Testing Advance exec */
    // testAdvanceExec();

    /* A2 : Testing GameLoop */
    GameEngine::testGameEngine();

    // Player *p1 = new Player("Hoax");

    // MapLoader *mapLoader = new MapLoader();
    // Map x4 = *mapLoader->loadMap("../maps/europe.map");
    // Map *map4 = new Map(x4);
    // map4->validate();

    // vector<Territory *> europeTerritories = map4->getTerritories();
    // Territory *t1 = europeTerritories.at(0);
    // Territory *t2 = europeTerritories.at(1);
    // Territory *t3 = europeTerritories.at(2);

    // priority_queue<Territory *, vector<Territory *>, compareArmySize> priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    // priorityAttacking.push(t1);
    // priorityAttacking.push(t2);
    // priorityAttacking.push(t3);
    // cout << priorityAttacking.top()->getName();
    // cout << "Now pop!" << endl;
    // priorityAttacking.pop();
    // cout << priorityAttacking.top()->getName();

    return 0;
}
