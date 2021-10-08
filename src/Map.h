#pragma once
#define MAX_SIZE 255

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Territory {
public:
    //constructors and destructor
    Territory();

    Territory(int t_ID);

    Territory(string name);

    Territory(const Territory &t1);

    ~Territory();

    //getters and setters
    int getID() { return ID; };

    int getNeighbors() { return neighbors; };

    string getName() { return name; };

    int getNumberOfArmies() { return numArmies; };

    void setNeighbors(int n) { neighbors = n; };

    void setName(string n) { name = n; };

    void setNumberOfArmies(int n) { numArmies = n; };

    //operators
    Territory &operator=(const Territory &t); //overloaded assignment operator
    friend std::ostream &operator<<(std::ostream &out, const Territory &t); //overloaded stream insertion operator
    friend std::istream &operator>>(std::istream &in, const Territory &t); //overloaded stream extraction operator


private:
    int ID;
    string name;
    //Player* owner;
    int numArmies = 0;
    int neighbors = 0;
};

struct Continent {
    // Continent();
    // ~Continent();

    std::vector<Territory *> territories; //to show list of territories on creating a continent

    std::string name;
    int numOfTerritories;

};

class Map {
public:
    Map();

    ~Map();

    std::vector<Territory *> neightborsList[MAX_SIZE];
    std::vector<Territory *> territoryNodeList;
    std::vector<Continent *> continentList;
    std::vector<Territory *> continentNeightborsList;

    Territory *createTerritoryNode();

    int addEdge(Territory *u, Territory *v);//to create edges between territory nodes
    int createContinent(std::string cName, int numOfCountries);

    int addToContinent(int index, Territory *u);

    int DFS(Territory *currentTNode, std::vector<Territory *> *tNodeVec); //to traverse through the territory nodes
    bool isIn(Territory *currentTNode, std::vector<Territory *> *tNodeVec); //for checking if territory
    int territorySizeCheck();

    int subgraphCheck(int continentIdx, std::vector<Territory *> *graphVec);

    int validate();

    int duplicateCheck();

    std::vector<Territory *> getTerritories();

    void registerWithContinent(string continent, int bonusArmyCount, Territory *territory);

    void addTerritory(Territory *territory, vector<Territory *> neighborList);

private:
    int counter;
};

class MapLoader {
private:
    string mapFileName;
    vector<string> continentList;
    vector<Territory *> countryList;
    vector<vector<Territory *> > bordersList; //Vector of vector of territories to store borders lists
    vector<int> continentNb; //To store the index of each continent associated to each country
    vector<int> armiesNb; //To store the nb of armies for each continent

public:
    MapLoader();

    MapLoader(const MapLoader &other);

    MapLoader(string mapFile);

    ~MapLoader();

    // Operator functions
    friend std::ostream &operator<<(std::ostream &lhs, MapLoader *d);

    MapLoader &operator=(const MapLoader &rhs);


    virtual bool checkValidity();

    virtual Map *readMapFile(); //stores all information into map
    virtual vector<string> readMapFileForContinents(); //reads file & return list of continents
    virtual vector<vector<Territory *> > readMapFileForBorders(); //reads file & return list of borders for each country
    virtual vector<Territory *> readMapFileForCountries(); //reads file & return list of countries
    virtual Map *combineInfos(); //stores all information into map

    vector<string> getContinentList();

    vector<Territory *> getCountryList();

    vector<vector<Territory *> > getBordersList();

    vector<int> getContinentNb();

    void setArmiesNb(vector<int> *armiesNumList);

    vector<int> getArmiesNb();

    void setMapFileName(string mapFile);

    string getMapFileName();
};
