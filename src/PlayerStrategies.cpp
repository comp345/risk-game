#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include <algorithm>
#include "Orders.h"

PlayerStrategy::PlayerStrategy()
{
}

PlayerStrategy::PlayerStrategy(Player *p)
{
    this->p = p;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps)
{
    this->p = new Player(*ps.p);
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &ps) {
    if (this == &ps)
        return *this;

    p = new Player(*ps.p);
    return *this;
}


PlayerStrategy::~PlayerStrategy(){
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





NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p)
{
};

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

// NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& p){
// }
// NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &ps){
//     if (this == &ps)
//         return *this;
//     return *this;
// }

void NeutralPlayerStrategy::issueOrder(Order* o)
{
    getPlayer()->getOrderList()->add(o);
}

vector<Territory *> NeutralPlayerStrategy::toAttack()
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

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string NeutralPlayerStrategy::strategyName()
{
    return "Neutral strategy";
}
