#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include <algorithm>
#include "Orders.h"

// ********************************** //
//      PlayerStrategy functions:     //
// ********************************** //
PlayerStrategy::PlayerStrategy()
{
}

PlayerStrategy::PlayerStrategy(Player *p)
{
    this->p = p;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &ps)
{
    this->p = new Player(*ps.p);
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &ps)
{
    if (this == &ps)
        return *this;

    p = new Player(*ps.p);
    return *this;
}

PlayerStrategy::~PlayerStrategy()
{
    delete p;
    p = NULL;
}
Player *PlayerStrategy::getPlayer()
{
    return p;
}

void PlayerStrategy::setPlayer(Player *p)
{
    this->p = p;
}


// ************************************************ //
//      AggressivePlayerStrategy functions:         //
// ************************************************ //

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p){};

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

void AggressivePlayerStrategy::issueOrder(Order *o)
{
    getPlayer()->getOrderList()->add(o);
}

vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    vector<Territory *> attackableTerritories = vector<Territory *>();

    //Get the players territories
    for (Territory *territory : getPlayer()->getTerritories())
    {
        //add them to the attackable Territories if they have an army on them
        if (territory->getNumberOfArmies() > 0)
            attackableTerritories.push_back(territory);
    }

    vector<Territory *> neighbourTerritories = vector<Territory *>();
    for (Territory *territory : attackableTerritories)
    {

        // cout << "the neighbours of " << territory->getName() << " are as follows:\n";
        for (Territory *neighbour : territory->getNeighbors())
        {
            // cout << neighbour->getName() << ", owned by " << neighbour->getOwner()->getName() <<"\n";

            // If we haven't already seen the territory, add it to the list.
            if (!count(neighbourTerritories.begin(), neighbourTerritories.end(), neighbour))

                // If it already belongs to us then we dont have to attack it.
                if (neighbour->getOwner() != getPlayer())
                    neighbourTerritories.push_back(neighbour);
        }
    }

    return neighbourTerritories;
};

vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string AggressivePlayerStrategy::strategyName()
{
    return "Aggressive strategy";
}



// ************************************************ //
//        BenevolentPlayerStrategy functions:       //
// ************************************************ //


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p){};

BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

void BenevolentPlayerStrategy::issueOrder(Order *o)
{
    getPlayer()->getOrderList()->add(o);
}

vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    //Since a benevolent player never advances to an enemy territory,
    //All this advance orders will target his own territories.

    //Get the list of the players territories:
    vector<Territory*> playersTerritoriesWithArmy = vector<Territory*>();

    //Make sure there is atleast one army on the territory:
    for(Territory* territory : getPlayer()->getTerritories()){
        if(territory->numArmies > 0)
            playersTerritoriesWithArmy.push_back(territory);
    }


    vector<Territory*> adjacentToPlayerTerritories = vector<Territory*>();

    //For each of the territories owned by the player
    for(Territory* playerTerritory : playersTerritoriesWithArmy){

        //Get their adjacent territories
        for(Territory* adjacentPlayerTerritory : playerTerritory->getNeighbors()){

            //Make sure it is your own territory:
            if(adjacentPlayerTerritory->getOwner() == getPlayer())

            //Build their adjacency list:
            adjacentToPlayerTerritories.push_back(adjacentPlayerTerritory);
        }
    }

    return getPlayer()->getTerritories();
};

vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string BenevolentPlayerStrategy::strategyName()
{
    return "Benevolent strategy";
}


// ********************************************* //
//        NeutralPlayerStrategy functions:       //
// ********************************************* //

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p){hasBeenAttacked = false;};

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

void NeutralPlayerStrategy::issueOrder(Order *o)
{
    if(hasBeenAttacked == true){
        cout << "DEBUG:: " << getPlayer()->getName() << " use to be a " << getPlayer()->getPlayerStrategy()->strategyName();
        getPlayer()->setPlayerStrategy(new AggressivePlayerStrategy(getPlayer()));
        cout << " and is now a " << getPlayer()->getPlayerStrategy()->strategyName();
    }
}

vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    //Doesnt issue any orders, do we need to return an attacking list?
    return getPlayer()->getTerritories();
};

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string NeutralPlayerStrategy::strategyName()
{
    return "Neutral strategy";
}

void NeutralPlayerStrategy::toggleHasBeenAttacked(){
    if(hasBeenAttacked) {
        hasBeenAttacked = false;
    }else {
        hasBeenAttacked = true;
    }
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &ps)
{
    cout << "COPY CTOR CALLED @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    this->hasBeenAttacked = ps.hasBeenAttacked;
}

NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &ps)
{
    cout << "ASSIGNEMNT OPERATOR CALLED @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    if (this == &ps)
        return *this;

    this->hasBeenAttacked = ps.hasBeenAttacked;
    return *this;
}