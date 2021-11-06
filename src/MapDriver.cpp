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

int main()
{
    testMap();
}
