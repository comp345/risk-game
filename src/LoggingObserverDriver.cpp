#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"
#include <iostream>
#include "CommandProcessor.h"
#include "Player.h"
#include "Map.h"

using namespace std;

Deploy * createDeployOrder();

void testLogging()
{
    GameEngine* engine = new GameEngine();
    LogObserver* observer = new LogObserver();
    engine->attach(observer);

    // transition engine to next state
    engine->doTransition("loadmap"); // current state is "start". valid transition is "loadmap"
    //------------------
    OrderList* ol = new OrderList();
    Deploy* deployOrder = createDeployOrder();
    ol->attach(observer);
    ol->add(deployOrder);
    //------------------
    deployOrder->attach(observer);
    deployOrder->execute();
    //------------------
    Command* command = new Command("loadmap", "map is loaded");
    command->attach(observer);
    command->saveEffect("loadmap");
    //------------------
    CommandProcessor* cp = new CommandProcessor();
    cp->attach(observer);
    cp->saveCommand(command);

    delete engine;
    delete observer;
    delete deployOrder;
}

Deploy * createDeployOrder() {
    int army = 4;
    Player *p1 = new Player("Laila");

    MapLoader *mapLoader = new MapLoader();
    Map x4 = *mapLoader->loadMap("../maps/europe.map");
    Map *map4 = new Map(x4);
    map4->validate();

    vector<Territory *> europeTerritories = map4->getTerritories();
    Territory *t1 = europeTerritories.at(0);

    // To create a valid territory, need to specify owner and number of armies (if territory is conquered)
    t1->setNumberOfArmies(5);
    t1->setOwner(p1);

    // Creating 2 distinct Deploy objects with same parameters should result in orders that execute on same Player and Territory
    Deploy *d1 = new Deploy(army, p1, t1);
    return d1;
}

//int main()
//{
//    testLogging();
//}