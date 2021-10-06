#pragma once
#ifndef MAP_H
#define MAP_H
#define MAX_SIZE 255

#include <vector>
#include <string>

class Territory{
    public:
        //constructors and destructor
        Territory();
        Territory(int t_ID);
        Territory(const Territory& t1);
        ~Territory();

        //getters and setters
        int getID(){return ID;};
        int getNeighbors(){return neighbors;};
        int getNumberOfArmies(){return numArmies;};

        void setNeighbors(int n){n=neighbors;};
        void setNumberOfArmies(int n){numArmies=n;};

        //operators
        void operator=(const Territory& t); //overloaded assignment operator
        friend std::ostream& operator<< (std::ostream& out, const Territory& t); //overloaded stream insertion operator
        friend std::istream& operator>> (std::istream& in, const Territory& t); //overloaded stream extraction operator


    private:
        int ID;
        int numArmies=0;
        int neighbors= 0;
};
struct Continent{
    Continent();
    ~Continent();

    std::vector<Territory*> territories; //to show list of territories on creating a continent
    
    std:: string name;
    int numOfTerritories;

};
class Map{
    public:
        Map();
        ~Map();
        std::vector<Territory*> neightborsList[MAX_SIZE];
        std::vector<Territory*> territoryNodeList;
        std::vector<Continent*> continentList;
        std::vector<Territory*> continentNeightborsList;
        Territory* createTerritoryNode();
        int addEdge(Territory* u, Territory* v);//to create edges between territory nodes
        int createContinent(std::string cName, int numOfCountries);
        int addToContinent(int index, Territory* u);
        int DFS(Territory* currentTNode, std::vector<Territory*>* tNodeVec); //to traverse through the territory nodes
        bool isIn(Territory* currentTNode, std::vector<Territory*>* tNodeVec); //for checking if territory 
        int territorySizeCheck();
        int subgraphCheck(int continentIdx, std::vector<Territory*>* graphVec);
        int validate();
        int duplicateCheck();
        std::vector<Territory*> getTerritories();
    private:
    int counter;
};
#endif
