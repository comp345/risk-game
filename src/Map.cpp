#include "Player.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::distance;
using std::endl;
using std::getline;
using std::ifstream;
using std::stoi; //conversion string to integer
using std::string;
using std::stringstream;
using std::vector;

Territory::Territory()
{
    ID = 0;
    numArmies = 0;
    neighbors = vector<Territory *>();
    owner = new Player;
}

Territory::Territory(int t_ID)
{
    ID = t_ID;
    numArmies = 0;
    neighbors = vector<Territory *>();
    owner = new Player;
}

// Noah note for A2: Deep copy, added deep copy owner
Territory::Territory(const Territory &t1)
{
    ID = t1.ID;
    name = t1.name;
    numArmies = t1.numArmies;
    owner = new Player(*t1.owner);
    neighbors = vector<Territory *>();
    for (auto it : t1.neighbors)
    {
        neighbors.push_back(new Territory(*it));
    }
}

Territory::~Territory() {}

// Noah note for A2: Deep copy, add copy owner (Player type)
Territory &Territory::operator=(const Territory &t)
{
    if (this == &t)
        return *this;
    ID = t.ID;
    name = t.name;
    numArmies = t.numArmies;
    if (owner)
        delete owner;
    owner = new Player(*t.owner);
    if (neighbors.size() > 0)
    {
        for (vector<Territory*>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            delete (*it);
        }
    }
    neighbors.clear();

    for (auto it : t.neighbors)
    {
        neighbors.push_back(new Territory(*it));
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Territory &t)
{
    out << "\tTerritory Name: " << t.name;
    out << "\t\tTerritory Number of Armies: " << t.numArmies;
    return out;
}

std::istream &operator>>(std::istream &in, const Territory &t)
{
    std::cout << "Enter territory ID: ";
    in >> t.ID;
    return in;
}

Territory::Territory(string n)
{
    ID = 0;
    numArmies = 0;
    // neighbors = 0;
    name = n;
}

int Territory::getID()
{
    return ID;
}

string Territory::getName()
{
    return name;
}

int Territory::getNumberOfArmies()
{
    return numArmies;
}

Player *Territory::getOwner()
{
    return owner;
}

// void Territory::setNeighbors(int n) {
//     neighbors = n;
// }

void Territory::setName(string n)
{
    name = n;
}

void Territory::setOwner(Player *p)
{
    owner = p;
}

vector<Territory *> Territory::getNeighbors()
{
    return neighbors;
}

void Territory::setNumberOfArmies(int n)
{
    numArmies = n;
}

void Territory::addNeighbor(Territory *t)
{
    neighbors.push_back(t);
}
/** TODO: Check this works   */
bool Territory::isNeighbor(Territory *t)
{
    for (Territory* n : getNeighbors()) {
        if (n == t) {
            return true;
        }
    }
    return false;
}

Continent::Continent()
{
    name = "";
    numOfTerritories = 0;
}

Continent::~Continent() {}

std::vector<Territory *> Map::getTerritories()
{
    return territoryNodeList;
}

//creates empty map
Map::Map()
{
    counter = 0;
}

Map::~Map() {
    neighborsList->clear();
    continentList.clear();
    territoryNodeList.clear();

    for (Continent *c: continentList) {
        delete c;
        c = nullptr;
    }
    for (Territory *t: territoryNodeList) {
        delete t;
        t = nullptr;
    }
    for (vector<Territory *> t: neighborsList) {
        t.clear();
    }
}

//creating a territory node inside map with a counter to count list of territories
Territory *Map::createTerritoryNode()
{
    Territory *t = new Territory(counter);
    counter++;
    return t;
}

bool Territory::operator<(const Territory &rhs) {
    return (this->numArmies <= rhs.numArmies);
}

//Initialized nodes for countries and neighbors
int Map::initList()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        territoryNodeList.push_back(createTerritoryNode());
        neighborsList[i].push_back(territoryNodeList.back());
    }
    return 0;
}


//add edge between territories
void Map::addEdge(Territory *u, Territory *v)
{
    neighborsList[u->getID()].push_back(v); //adds new territory V after the territory u in the vector
    territoryNodeList.at(u->getID())->addNeighbor(v);
}

//create a continent with name and list of countries
void Map::createContinent(std::string cName, int numOfCountries, int armiesNum)
{
    Continent *c = new Continent();
    c->name = cName;
    c->numOfTerritories = numOfCountries;
    c->controlBonus = armiesNum;
    continentList.push_back(c);
    c = nullptr;
}

//add territories to created continent
void Map::addToContinent(int index, Territory *u)
{
    Continent *c = continentList.at(index);
    c->territories.push_back(u);
    c->numOfTerritories++;
    c = nullptr;
}

//helper method for graph traversal-> check territory size
int Map::getTerritorySize()
{
    int tNodeCounter = 0;

    for (int i = 0; i < continentList.size(); i++)
    {
        tNodeCounter += continentList[i]->territories.size();
    }
    return tNodeCounter;
}

//helper method for graph traversal-> check if current territory node (using ID) is part of the territory node vector
bool Map::isIn(Territory *currentTNode, std::vector<Territory *> *tNodeVec)
{
    for (int i = 0; i < tNodeVec->size(); i++)
    {
        if (currentTNode->getID() == (*tNodeVec)[i]->getID())
        {
            return true;
        }
    }
    return false;
}

//traverse using DFS & compare current territory node to the territory node vector
void Map::DFS(Territory *currentTNode, std::vector<Territory *> *tNodeVec)
{
    if (isIn(currentTNode, tNodeVec))
    { //no need to traverse current node
        return;
    }
    (*tNodeVec).push_back(currentTNode); //add territories that have been traversed

    for (int i = 0; i < neighborsList[currentTNode->getID()].size(); i++)
    {
        if (!isIn(neighborsList[currentTNode->getID()].at(i), tNodeVec))
        {
            DFS(neighborsList[currentTNode->getID()].at(i), tNodeVec);
        }
    }
}

//helper method for duplicate territory check
bool Map::containsDuplicateTerritories()
{
    cout << "\nChecking for non duplicate territories: \n";

    for (int i = 0; i < continentList.size() - 1; i++)
    {
        for (int j = 0; j < continentList[i]->territories.size(); j++)
        {
            for (int k = i + 1; k < continentList.size(); k++)
            {
                for (int l = 0; l < continentList[k]->territories.size(); l++)
                {
                    if (continentList[i]->territories[j] == continentList[k]->territories[l])
                    {
                        cout << "ERROR: Duplicate territory found! \n";
                        std::cout << continentList[i]->name << "--->" << continentList[i]->territories[j]->getName()
                                  << "\t";
                        std::cout << continentList[k]->name << "--->" << continentList[k]->territories[l]->getName()
                                  << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    cout << "\nNo duplicate territories found!\n";
    return false;
}

//helper method check if subgraph is connected
bool Map::isAConnectedSubgraph(int continentIdx, std::vector<Territory *> *graphVec)
{
    for (int i = 0; i < continentList.size(); i++)
    {
        if (i != continentIdx)
        {
            for (int j = 0; j < continentList[i]->territories.size(); j++)
            {
                graphVec->push_back(continentList[i]->territories[j]);
            }
        }
    }
    DFS(continentList[continentIdx]->territories[0], graphVec);
    if (graphVec->size() == getTerritorySize())
    {
        std::cout << "\n"
                  << continentList[continentIdx]->name << ": is a connected subgraph" << std::endl;
        return true;
    }
    else
    {
        std::cout << "\n"
                  << continentList[continentIdx]->name << ": is not a connected subgraph" << std::endl;
        return false;
    }
}

//map validation method
bool Map::validate()
{
    std::vector<Territory *> visitedTerritory;
    int tSize = getTerritorySize();
    if (tSize == 0)
    {
        return false;
    }

    DFS(continentList[0]->territories[0], &visitedTerritory);

    if (visitedTerritory.size() == tSize)
    {
        cout << "This is a connected graph \n";
    }
    else
    {
        cout << "The map is not a connected graph! \n";
        return false;
    }

    if (containsDuplicateTerritories())
    {
        return false;
    }

    for (int i = 0; i < continentList.size(); i++)
    {
        std::vector<Territory *> sub;
        if (!isAConnectedSubgraph(i, &sub))
        {
            return false;
        }
    }
    cout << "\n";
    return true;
}
void Map::showLoadedMap() {
    Continent continent;
    //cout<<"Showing content of "<<continent.name <<" and its territories: \n"<<endl;

    for(int i=0; i<continentList.size();i++){
        cout<<"Showing "<<continentList[i]->name<<" and its adjacents:\n \t"<<endl;
        for(int j=0;j<continentList[i]->territories.size();j++){
            cout<<"-> "<<continentList[i]->territories[j]->getID()<<endl;
        }
        //cout<<"\n"<<endl;
    }
    cout<<"\n \n"<<endl;

}
Map &Map::operator=(const Map &m)
{
    // self-assignment guard
    if (this == &m)
        return *this;
    territoryNodeList=m.territoryNodeList;
    continentList=m.continentList;
    counter=m.counter;
    return *this;
}
ostream &operator<<(ostream &out,  Map &m)
{
//    string command = o.command;
//    string details = o.details;
//    // insert every data field (to do)
//    out << "{ Order object: Command type(" << command << "), Details(" << details << ")}";
//    out<<m.territoryNodeList<<endl;
//    for (vector<Territory *>::iterator it = m.territoryNodeList.begin(); it != m.territoryNodeList.end(); ++it)
//    {
//        out << " "
//             << (**it).getName();
//    }

    return out;
}

// ********************** //
// Map Loader functions:  //
// ********************** //
MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

std::vector<std::string> MapLoader::splitString(std::string str, const char separator)
{
    vector<string> parts;
    stringstream lineStringStream(str);
    string part;

    while (getline(lineStringStream, part, separator)) //split line at the comma
    {
        parts.push_back(part); //add content to vector parts
    }

    return parts;
}

bool MapLoader::getMapStatus()
{
    return mapStatus;
}

void MapLoader::goTo(std::fstream &infile, std::string header)
{
    infile.clear();
    infile.seekg(0);

    string line;
    while (std::getline(infile, line))
    {
        if (line.find(header) != std::string::npos)
        {
            break;
        }
    }
}

bool MapLoader::containsHeader(std::fstream &infile, std::string header)
{
    infile.clear();
    infile.seekg(0);

    string line;
    bool found = false;

    while (std::getline(infile, line))
    {
        if (line.find(header) != std::string::npos)
        {
            found = true;
        }
    }

    if (!found)
    {
        cout << "Warning: File doesn't contain " << header << endl;
    }

    infile.clear();
    infile.seekg(0);

    return found;
}

//copy constructor
MapLoader::MapLoader(const MapLoader &ml1)
{
    ID = ml1.ID;
}

//operator overload
MapLoader &MapLoader::operator=(const MapLoader &ml)
{
    if (this == &ml)
        return *this;

    ID = ml.ID;
    return *this;
}

ostream &operator<<(ostream &out, const MapLoader &ml)
{
    out << endl
        << "\tMapLoader ID: " << ml.ID << endl;
    return out;
}

istream &operator>>(std::istream &in, MapLoader &ml)
{
    std::cout << "Enter MapLoader ID: ";
    in >> ml.ID;
    return in;
}

//Method to load map from a .map file
Map *MapLoader::loadMap(string fileName)
{
    cout << "\n -----------------------------" << endl;
    cout << "\nLoading map from file..... " << fileName << endl;
    fstream infile;
    infile.open(fileName);
    Map *graph = new Map();

    //check if the map follows the conquest map format
    if (!containsHeader(infile, "[files]") || !containsHeader(infile, "[continents]") || !containsHeader(infile, "[countries]") || !containsHeader(infile, "[borders]"))
    {
        mapStatus = false;
        return graph;
    }

    graph->initList();
    string line;

    //go to until [Continents]
    goTo(infile, "[continents]");

    int continentIndex = 1;
    //while haven't reached [countries]
    while (getline(infile, line) && line.compare("[countries]"))
    {
        if (line.empty())
        {
            continue;
        } //skip empty lines
        std::vector<std::string> lineVector = splitString(line, ' ');
        string continentName = lineVector.at(0);
        int numOfArmies = stoi(lineVector.at(1));
        graph->createContinent(continentName, continentIndex, numOfArmies);
        continentIndex++;
    }

    //go to [countries]
    goTo(infile, "[countries]");

    //set countries in continent from [countries] to
    while (getline(infile, line) && line.compare("[borders]"))
    {
        //skip empty lines
        if (line.empty())
        {
            continue;
        }

        //extract details from the row
        std::vector<std::string> lineVector = splitString(line, ' ');
        int countryIndex = stoi(lineVector.at(0));
        string countryName = lineVector.at(1);
        int continentIndex = stoi(lineVector.at(2));

        //set country in corresponding continent
        graph->territoryNodeList[countryIndex - 1]->setName(countryName);
        graph->addToContinent(continentIndex - 1, graph->territoryNodeList[countryIndex - 1]);
    }

    //go to [borders]
    goTo(infile, "[borders]");

    //set borders
    while (getline(infile, line))
    {
        std::vector<std::string> lineVector = splitString(line, ' ');

        int countryIndex = stoi(lineVector.at(0));
        lineVector.erase(lineVector.begin());

        for (const string &stringNeighbor : lineVector)
        {
            int neighbor = stoi(stringNeighbor);
            graph->addEdge(graph->territoryNodeList[countryIndex - 1], graph->territoryNodeList[neighbor - 1]);
        }
    }

    infile.close();
    auto it = graph->territoryNodeList.begin();
    while (it != graph->territoryNodeList.end())
    {
        // remove empty territories
        if ((*it)->getName() == "")
        {
            // `erase()` invalidates the iterator, use returned iterator
            it = graph->territoryNodeList.erase(it);
        }
        else {
            ++it;
        }
    }
    return graph;
}