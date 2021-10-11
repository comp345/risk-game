#pragma once
#define MAX_SIZE 255

#include <vector>
#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Player;

class Territory {
public:
    //constructors and destructor
    Territory();

    Territory(int t_ID);

    Territory(string name);

    Territory(const Territory &t1);

    ~Territory();

    //getters and setters
    int getID();

    Player* getOwner();

    int getNeighbors();

    string getName();

    int getNumberOfArmies();

    void setNeighbors(int n);

    void setName(string n);

    void setOwner(Player* p);

    void setNumberOfArmies(int n);

    //operators
    Territory &operator=(const Territory &t); //overloaded assignment operator
    friend std::ostream &operator<<(std::ostream &out, const Territory &t); //overloaded stream insertion operator
    friend std::istream &operator>>(std::istream &in, const Territory &t); //overloaded stream extraction operator


private:
    int ID;
    string name;
    Player* owner;
    int numArmies = 0;
    int neighbors = 0;
};

struct Continent {
    Continent();
    ~Continent();

    std::vector<Territory *> territories; //to show list of territories on creating a continent

    std::string name;
    int numOfTerritories;
    int numOfArmies;
};

class Map {
public:
    Map();

    ~Map();

    std::vector<Territory *> neighborsList[MAX_SIZE];
    std::vector<Territory *> territoryNodeList;
    std::vector<Continent *> continentList;

    Territory *createTerritoryNode();

    void addEdge(Territory *u, Territory *v);//to create edges between territory nodes
    void createContinent(std::string cName, int numOfCountries, int armyNum);

    void addToContinent(int index, Territory *u);

    void DFS(Territory *currentTNode, std::vector<Territory *> *tNodeVec); //to traverse through the territory nodes
    bool isIn(Territory *currentTNode, std::vector<Territory *> *tNodeVec); //for checking if territory
    int getTerritorySize();
    int initList();

    bool isAConnectedSubgraph(int continentIdx, std::vector<Territory *> *graphVec);

    bool validate();

    bool containsDuplicateTerritories();

    std::vector<Territory *> getTerritories();

private:
    int counter;
};
class MapLoader {
public:
    MapLoader();
    ~MapLoader();
    //copy constructor
    MapLoader(const MapLoader& ml1);

    //Assignment operator
    MapLoader& operator=(const MapLoader& ml);
    friend std::ostream& operator<<(std::ostream& out, const MapLoader& ml);
    friend std::istream& operator>>(std::istream& in, MapLoader& ml);

    std::vector<std::string> splitString(std::string str, const char separator);
    Map* loadMap(std::string fileName);
    int ID;
    bool getMapStatus();

private:
    void goTo(std::fstream& infile, std::string header);
    bool containsHeader(std::fstream& infile, std::string header);
    bool mapStatus = true;
}; 