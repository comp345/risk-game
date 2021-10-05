#include "Map.h"
#include <vector>


Territory::Territory(){
    ID=0;
    numArmies=0;
    neighbors=0;
}
Territory::Territory(int tID){
    ID=tID;
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
