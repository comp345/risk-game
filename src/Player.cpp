#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
    territories = vector<Territory *>();
    hand = new Hand();
    orderList = new OrderList();
}

Player::Player(string n)
{
    this->name = n;
    this->hand = new Hand();
    this->orderList = new OrderList();
}

//parametrized constructor
Player::Player(string n, vector<Territory*> t, Hand* h, OrderList* o)
{
    this->name = n;
    this->territories = t;
    this->hand = h;
    this->orderList = o;
}

//copy constructor
Player::Player(const Player& p)
{
    this->name = p.name;
    this->territories = p.territories;
    this->hand = p.hand;
    this->orderList = p.orderList;
}

//destructor
Player::~Player()
{
    territories.clear();
    delete orderList;
    orderList = nullptr;
    delete hand;
    hand = nullptr;

    for (Territory* t : territories) {
        delete t;
        t = nullptr;
    }
}

//operator overloading
//assignment operator overloading
Player& Player::operator=(const Player& p) {
    if (this == &p)
        return *this;

    territories = p.territories;
    hand = new Hand(*(p.hand));
    orderList = new OrderList(*(p.orderList));
    return *this;
}

//stream insertion operator overloading
ostream& operator<<(ostream& out, const Player& p) {
    out << "Territories: " << endl;
    for (Territory* t : p.territories) {
        out << *t << endl;
    }

    if (p.orderList != nullptr) {
        for (Order* o : p.orderList->getList()) {
            out << "Orders: " << *o << endl;
        }
        out << "Orders should be printing here\n";
    }

    else {
        out << "\nOrders not initialized";
    }

    if (p.hand != nullptr) {
        for (Card* c : p.hand->getCards()) {
            out << "\nCard: " << c << endl;
        }
    }

    else {
        out << "\nHand not initialized";
    }

    return out;
}

istream& operator>>(istream& in, Player& p) {
    in >> p.name;
    return in;
}

//returns a list of territories to attack
vector<Territory *> Player::toAttack()
{
    return territories;

}

//returns a list of territories to defend
vector<Territory *> Player::toDefend()
{
    return territories;
}

//adds order to a player's list of orders
void Player::issueOrder(string order, string details)
{
    //TODO: delete?
//    Order* o = new Order(order, details);
//    orderList->add(o);
}

//adds order to a player's list of orders
void Player::issueOrder(Order* o)
{

    // decides which neighboring territories are to be attacked
    for (Territory* toAttack : toAttack())
    {
        // Make a new list with users priority?
    }


    // decides which neighboring territories are to be defended
    for (Territory* toDefend : toDefend())
    {
        // Make a new list with users priority?
    }

    // As long as the player has armies still to deploy
    if(reinforcementPool != 0)
    {
        // it will issue a deploy order and no other order.
        if(o->getCommand() != "deploy"){
            cout << "Since there are still reinforcements in this players pool, you must places all arimies first.";
            return;
        }
    }


    // The player issues advance orders
    if(o->getCommand() == "advance"){

        // move armies from one of its own territory to the other in order to defend them
        

        // move armies from one of its territories to a neighboring enemy territory to attack them 
    }


    orderList->add(o);
    
}

Hand *Player::getHand() {
    return hand;
}

vector<Territory *> Player::getTerritories() {
    return territories;
}

string Player::getName() {
    return name;
}

OrderList *Player::getOrderList() {
    return orderList;
}

void Player::setTerritories(vector<Territory *> terr) {
    territories = terr;
}

void Player::setCards(Hand *pHand) {
    hand = pHand;
}

//Goes through all the orders that are in the list of orders of a given player and prints them
void Player::printOrders()
{
    cout << "\nPlayer: " << name << " Has the following ordered queued\n";
    for(Order* o : orderList->getList())
    {
        cout << *o << "\n";
    }
}
