#include "Map.h"
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::string;
using std::ifstream;
using std::stringstream;
using std::stoi; //conversion string to integer
using std::distance;

Territory::Territory(){
    ID=0;
    numArmies=0;
    neighbors=0;
}
Territory::Territory(int t_ID){
    ID=t_ID;
    numArmies=0;
    neighbors=0;
}
Territory::Territory(const Territory& t1){
    std::cout <<"Copy constructor" << std::endl;
    ID= t1.ID;
}
Territory::~Territory(){}

Territory::void operator=(const Territory& t){
    std::cout <<"Assignment operator"<< std::endl; 
    ID= t.ID;
    numArmies=t.numArmies;
}
std::ostream& operator<< (std::ostream& out, const Territory& t){
    out << std::endl << "\tTerritory ID: " << t.ID << std::endl;
	out << "\tTerritory Number of Armies: " << t.numberOfArmies;
	return out;
}
std::istream& operator>> (std::istream& in, const Territory& t){
    std::cout << "Enter territory ID: ";
	in >> t.ID;
	return in;
}

Continent::Continent(){
    name="";
    numOfTerritories==0;
}
Continent::~Continent(){}

std::vector<Territory*> Map::getTerritories(){
    return territoryNodeList;
}

//creates empty map
Map::Map() {
	counter = 0;
}

Map::~Map() {}

//creating a territory node inside map with a counter to count list of territories
Territory* Map::createTerritoryNode(){
    Territory* t= new Territory(counter);
    counter++;
    return t;
}

//add edge between territories
int Map::addEdge(Territory* u, Territory* v) {
	neightborsList[u->getID()].push_back(v); //adds new territory V after the territory u in the vector
	return 0;
}

//create a continent with name and list of countries
int Map::createContinent(std::string cName, int numOfCountries){
    Continent* c= new Continent();
    c->name= cName;
    c->numOfTerritories= numOfCountries;
    continentList.push_back(c);
    c= nullptr;
    return 0;
}

//add territories to created continent
int Map::addToContinent(int index, Territory* u){
    Continent* c= continentList.at(index);
    c->territories.push_back(u);
    c->numOfTerritories++;
    c=nullptr;
    return 0;
}

//helper method for graph traversal-> check territory size
int Map::territorySizeCheck(){
    int tNodeCounter=0;

    for(int i= 0; i< continentList.size(); i++){
        tNodeCounter+= continentList[i]->territories.size();
    }
    return tNodeCounter;
}

//helper method for graph traversal-> check if current territory node (using ID) is part of the territory node vector
bool Map::isIn(Territory* currentTNode, std::vector<Territory*>* tNodeVec){
    for(int i=0; i<tNodeVec->size(); i++){
        if(currentTNode->getID()==(*tNodeVec)[i]->getID()){
            return true;
        }
    }
    return false;
}
//traverse using DFS & compare current territory node to the territory node vector
int Map::DFS(Territory* currentTNode, std::vector<Territory*> *tNodeVec){
    if(isIn(currentTNode, tNodeVec)){//no need to traverse current node
        return false;
    }
    (*tNodeVec).push_back(currentTNode);//add territories that have been traversed

    for (int i=0; i < neightborsList[currentTNode->getID()].size; i++){
        if(!isIn(neightborsList[currentTNode->getID()].at(i), tNodeVec)){
            DFS(neightborsList[currentTNode->getID()].at(i), tNodeVec)''
        }
    }
}

//helper method for duplicate territory check
int Map::duplicateCheck(){
    printf("\n Checking for non duplicate territories: \n");

    for(int i=0; i<continentList.size()-1; i++){
        for(int j=0; j<continentList[i]->territories.size();j++){
            for(int k=i+1; k<continentList.size();k++){
                for(int l=0; l<continentList[k]->territories.size(); l++){
                    if(continentList[i]->territories[j] == continentList[j]->territories[l]){
                        printf("ERROR: Duplicate territory found! ")
                    }
                    std::cout<<continentList[i]->name <<continentList[i]->territories[j]->getID() << "\t";
                    std::cout<<continentList[k]->name <<continentList[k]->territories[l]->getID() << std::endl;
                }
            }
        }
    }
    printf("\n Map is valid: No duplicate territories found! \n")
    return 0;
}

//helper method check if subgraph is connected
int Map::subgraphCheck(int continentIdx, std::vector<Territory*>* graphVec){
    for (int i= 0; i<continentList.size(); i++){
        if( i!=continentIdx){
            for(int j=0; j< continentList[i]->territories.size(); j++){
                graphVec->push_back(continentList[i]->territories[j]);
            }
        }
    }
    DFS(continentList[continentIdx]->territories[0], graphVec);
    if(graphVec->size() == territorySizeCheck()){
        std::cout <<"\n"<<continentList[continentIdx]->name << ": is a connected subgraph"<< std::endl;
    }
    return 0;
}

//map validation method
int Map::validate(){
    std::vector<Territory*> visitedTerritory;
    int tSize= territorySizeCheck();

    DFS(continentList[0]->territories[0], &visitedTerritory);

    if(visitedTerritory.size() == tSize){
        printf("This is a connected graph \n")
    }

    for(int i=0; i< continentList.size(); i++){
        std::vector<Territory*> sub;
        subgraphCheck(i, &sub);
    }
    duplicateCheck();
    printf("\n");

    return 0;

}

bool MapLoader::checkValidity(string _inputFileStream) {
	cout << "\nChecking validity of map..." << endl;

	string line;
	ifstream ifs(_inputFileStream);

	string currentLine;

	while (getline(ifs, currentLine) && currentLine != "[continents]")
	{
		//While current line isn't equal to [Continents] skip 
	}

	if (currentLine != "[continents]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [continents] tag. Exiting program...\n\n";
		exit(0);
	}

	while (getline(ifs, currentLine) && currentLine != "[countries]")
	{
		//While current line isn't equal to [Territories] skip 
	}

	if (currentLine != "[countries]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [countries] tag. Exiting program...\n\n";
		exit(0);
	}

	while (getline(ifs, currentLine) && currentLine != "[borders]")
	{
		//While current line isn't equal to [Territories] skip 
	}

	if (currentLine != "[borders]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [borders] tag. Exiting program...\n\n";
		exit(0);
	}

    ifs.close();
    ifs.clear();

	cout << "Map is VALID and ready to be parsed." << endl;

	return true;
}

Map* MapLoader::readMapFile(string _inputFileStream) {
    Map* map = new Map();
    
    //Check validity
	bool isValid = checkValidity(_inputFileStream);
	if (isValid) {
		std::cout << "Map file is valid." << endl;

		//Add continents
		vector<string> continentList = {};
		continentList = readMapFileForContinents(_inputFileStream, continentList);

		//Add countries
		vector<Territory*> countryList = {};
		countryList = readMapFileForCountries(_inputFileStream, countryList);

		//Add borders
		vector<vector<Territory*>> bordersList = {};
		bordersList = readMapFileForBorders(_inputFileStream, bordersList, countryList);

		//Create the map
		if (!continentList.empty() && !countryList.empty() && !bordersList.empty() ) {
			map = combineInfos(continentList, countryList, bordersList);
            return map;
		}
	}
	else {
        //TODO: throw exception?
		cout << "\nMap file is invalid. Cannot create map." << endl;
	}
}

Map* MapLoader::combineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	Map* map = new Map();
	int currContinentNb;

	for (int i = 0; i < _countryList.size(); i++)
	{
		map->addTerritory(_countryList[i], _bordersList[i]);
		currContinentNb = continentNb[i] - 1;
		map->registerWithContinent(_continentList[currContinentNb], _countryList[i]);
	}
	cout << "\n";
	cout << "\n";
	return map;
}

vector<string> MapLoader::readMapFileForContinents(string _inputFileStream) {
	cout << "\nREGISTERING CONTINENTS" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int armies;
	string territoryName, continentName, color;
    vector<string> continentList;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[continents]") {
		};

		//first line
		inputFileStream >> continentName >> armies >> color;
		string continent = string(continentName);
		armiesNb.push_back(armies);
		continentList.push_back(continent);

		while (getline(inputFileStream, line) && line != "[continents]") {
			inputFileStream >> continentName >> armies >> color;

			if (continentName == "[countries]")
			{
				break;
			}
			string continent = string(continentName);
            armiesNb.push_back(armies);
			continentList.push_back(continent);
		}

		inputFileStream.close();

		return continentList;
	}

	cout << "File is not open " << "\n";
}

vector<Territory*> MapLoader::readMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList) {
	cout << "\nREGISTERING COUNTRIES" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continent, x, y;
	string territoryName;

	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line != "[countries]") {};

		//first line
		inputFileStream >> index >> territoryName >> continent >> x >> y;
		Territory* country = new Territory(territoryName);
		continentNb.push_back(continent);
		_countryList.push_back(country);

		while (getline(inputFileStream, line) && line != "[countries]") {

			inputFileStream >> index >> territoryName >> continent >> x >> y;
			if (territoryName == "[borders]" || territoryName == _countryList.at(_countryList.size() - 1)->getName())
			{
				break;
			}

			Territory* country = new Territory(territoryName);
			continentNb.push_back(continent);
			_countryList.push_back(country);
		}

		inputFileStream.close();
		inputFileStream.clear();
		std::cout << "Country list size: " << _countryList.size() << endl;
		return _countryList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}

vector<vector<Territory*>> MapLoader::readMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList) {
	cout << "\nREGISTERING BORDERS" << endl;

	string line;
	ifstream inputFileStream(_inputFileStream);

	vector<Territory*> nList;
	int i_subs;
	string::size_type sz;
	string subs;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[borders]") {}

		//first number
		inputFileStream >> line;
		i_subs = stoi(line, &sz);
		Territory* current = _countryList[i_subs - 1];
		nList.push_back(current);


		while (getline(inputFileStream, line) && line.find("[borders]") == std::string::npos) {
			nList = {};
			istringstream iss(line);

			do {
				iss >> subs;
				i_subs = stoi(subs, &sz);
				Territory* current = _countryList[i_subs - 1];
				nList.push_back(current);

			} while (iss);

			if (nList.at(nList.size() - 1)->getName() == nList.at(nList.size() - 2)->getName())
			{
				nList.pop_back();
			}

			_bordersList.push_back(nList);
		}

		inputFileStream.close();
		inputFileStream.clear();

		cout << "Borders list size: " << _bordersList.size() << endl;
		return _bordersList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}


