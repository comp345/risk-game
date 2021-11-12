#include "Player.h"
#include "Card.h"
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
// Noah note for A2: should not init Hand* and OrderList* to NULL (see default constructor)
Player::Player(string n, vector<Territory*> t, Hand* h, OrderList* o)
{
    this->name = n;
    this->territories = t;
    this->hand = h;
    this->orderList = o;
}

//copy constructor: Deep copy, cannot be used for reference semantic or to 
Player::Player(const Player& p) 
{
    // cout << "Entering Player::Player(const Player& p)" <<endl;
    this->name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*p.hand); 
    this->orderList = new OrderList(*p.orderList); 
    // cout << "Exiting Player::Player(const Player& p)" <<endl;
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
// Noah note for A2: Deep copy
Player& Player::operator=(const Player& p) {
    if (this == &p)
        return *this;

    territories = p.territories;
    if (hand) delete hand;
    if (orderList) delete orderList;
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
