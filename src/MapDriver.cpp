#include "Map.h"
#include <iostream>

using namespace std;

int main() {
    MapLoader *mapLoader = new MapLoader();
    Map x = *mapLoader->loadMap("../maps/invalid1.map");
    Map *map = new Map(x);
    map->isAValidMap();


    Map x2 = *mapLoader->loadMap("../maps/invalid2.map");
    Map *map2 = new Map(x2);
    map2->isAValidMap();


    Map x3 = *mapLoader->loadMap("../maps/invalid3.map");
    Map *map3 = new Map(x3);
    map3->isAValidMap();


    Map x4 = *mapLoader->loadMap("../maps/europe.map");
    Map *map4 = new Map(x4);
    map4->isAValidMap();


    Map x5 = *mapLoader->loadMap("../maps/france.map");
    Map *map5 = new Map(x5);
    map5->isAValidMap();


    Map x6 = *mapLoader->loadMap("../maps/artic.map");
    Map *map6 = new Map(x6);
    map6->isAValidMap();
}