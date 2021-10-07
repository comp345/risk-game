#pragma once
#define MAX_SIZE 255

#include <vector>
#include <string>
#include <iostream>

using namespace std;

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

class MapLoader {
    public:
		MapLoader();
		MapLoader(MapLoader&);
		MapLoader& operator=(MapLoader& h);

        virtual bool checkValidity(string _inputFileStream);
        virtual Map* readMapFile(string _inputFileStream); //stores all information into map
		virtual vector<string> readMapFileForContinents(string _inputFileStream, vector<string> _continentList); //reads file & return list of continents
		virtual vector<vector<Territory*>> readMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList); //reads file & return list of borders for each country
		virtual vector<Territory*> readMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList); //reads file & return list of countries
		vector<string> getContinentList(); 
		vector<Territory*> getCountryList();
		vector<vector<Territory*>> getBordersList();
		vector<int> getContinentNb();
        vector<int> SetArmiesNb(vector<int> *bonusControlList);
		vector<int> GetArmiesNb();

		friend ostream& operator << (ostream& out, MapLoader& hps);
	
		virtual Map* combineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map

    private:
		vector<string> continentList; 
		vector<Territory*> countryList;
		vector<vector<Territory*>> bordersList; //Vector of vector of territories to store borders lists
		vector<int> continentNb; //To store the index of each continent associated to each country
		vector<int> armiesNb; //To store the nb of armies for each continent
};
