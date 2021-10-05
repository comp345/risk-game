#pragma once
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

        std::vector<Territory*> territoryNodeList;
        std::vector<Continent*> continentList;
        std::vector<Territory*> continentNeightborsList;

        int addEdge(Territory* u, Territory* v);//to create edges between territory nodes
        
        int createContinent(std::string cName, int numOfCountries);
        int addToContinent(int index, Territory* u);
        int getContinentIndexByName(std::string name);
        
        int DFS(Territory* currentNode, std::vector<Territory*>* _nodeVec); //to traverse through the territory nodes
        bool isIn(Territory* currentNode, std::vector<Territory*>* nodeVec); //for checking if territory 
        
        Territory* createTerritoryNode();
        std::vector<Territory*> getTerritories();
        int territorySizeCheck();
        int subgraphCheck(int continentIndex, std::vector<Territory*>* vec);
        
        int validate();
        int duplicateCheck();

    private:
    int counter;
};