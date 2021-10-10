#include "Map.h"
#include <iostream>

using namespace std;

int main() {
	MapLoader* maploader = new MapLoader("../maps/france.map");
    Map* map = maploader->readMapFile();

//    MapLoader* maploader2 = new MapLoader("../maps/europe.map");
//    maploader2->readMapFile();
//
//    MapLoader* maploader3 = new MapLoader("../maps/sudoku.map");
//    maploader3->readMapFile();

    map->validate();

    return 0;
}