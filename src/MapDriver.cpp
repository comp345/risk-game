#include "Map.h"
#include <iostream>

using namespace std;

void testMap()
{
    MapLoader *mapLoader = new MapLoader();
    Map x = *mapLoader->loadMap("../maps/invalid1.map");
    Map *map = new Map(x);
    map->validate();

    Map x2 = *mapLoader->loadMap("../maps/invalid2.map");
    Map *map2 = new Map(x2);
    map2->validate();

    Map x3 = *mapLoader->loadMap("../maps/invalid3.map");
    Map *map3 = new Map(x3);
    map3->validate();

    //duplicate territory with same ID case (territory 20)
    Map x7 = *mapLoader->loadMap("../maps/hawaii.map");
    Map *map7 = new Map(x7);
    map7->validate();

    Map x4 = *mapLoader->loadMap("../maps/europe.map");
    Map *map4 = new Map(x4);
    map4->validate();

    Map x5 = *mapLoader->loadMap("../maps/france.map");
    Map *map5 = new Map(x5);
    map5->validate();

    //not connected map
    Map x6 = *mapLoader->loadMap("../maps/artic.map");
    Map *map6 = new Map(x6);
    map6->validate();

    //not connected subgraph continent case
    Map x8 = *mapLoader->loadMap("../maps/estonia.map");
    Map *map8 = new Map(x8);
    map8->validate();
}

void testA2Map()
{

    // ********************************** //
    //   Init parameters for testing      //
    // ********************************** //
    int army = 4;

    MapLoader *mapLoader = new MapLoader();
    Map x4 = *mapLoader->loadMap("../maps/europe.map");
    Map *map0 = new Map(x4);
    map0->validate();

    vector<Territory *> europeTerritories = map0->getTerritories();
    int numberOfTerritoryInEurope = map0->getTerritorySize();

    Player *p1 = new Player("Hoax");
    Player *p2 = new Player("Toast");

    // ********************************** //
    //   Test Territory Copy Constructor  //
    // ********************************** //
    Territory* englandPtr = new Territory(*europeTerritories.at(0));
    Territory* t0 = new Territory(*englandPtr);
    Territory* t1 = new Territory(*englandPtr);
    // Result: These are all deep copy of the pointer to europeTerritories.at(0)
    cout << "address of the territory pointed at by englantPtr: " << &(*englandPtr) << ". *englandPtr: " << *englandPtr << endl; // Address 1, point to
    cout << "address of the territory pointed at by t0: " << &(*t0) << ". *t0: " << *t0 << endl; // Address 1, point to
    cout << "address of the territory pointed at by t1: " << &(*t1) << ". *t1: " << *t1 << endl;

    // Check if, as t0 and t1 point to the same territory: Change ownership.
    t0->setName("Not england"); // Desired result: *t0 and *t1 will be named "Not england"
    cout << "Chanding Name of England:" << endl;
    cout << "address of the territory pointed at by t0: " << &(*t0) << ". *t0: " << *t0 << endl; // Address 1, point to
    cout << "address of the territory pointed at by t1: " << &(*t1) << ". *t1: " << *t1 << endl;

    cout << endl
         << endl;
}