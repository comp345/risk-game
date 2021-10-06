#include "Map.h"
#include <vector>
#include <iostream>
#include <queue>

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



