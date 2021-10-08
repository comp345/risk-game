#include "Map.h"
#include <iostream>

using namespace std;

int main() {
	MapLoader* maploader = new MapLoader();

    maploader->readMapFile("../maps/france.map");
    return 0;
}