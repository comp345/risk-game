#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
    string name;
    vector<Territory*> territories;
    Hand* hand;
    OrderList* orderList;
}

Player::Player(string n)
{
    this->name = n;
}


Player::Player(string n, vector<Territory*> t, Hand* h, OrderList* o)
{
    this->name = n;
    this->territories = t;
    this->hand = h;
    this->orderList = o;
}

Player::Player(const Player& p)
{
    this->name = p.name;
    this->territories = p.territories;
    this->hand = p.hand;
    this->orderList = p.orderList;
}

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

vector<Territory *> Player::toAttack()
{
    return territories;

}

vector<Territory *> Player::toDefend()
{
    return territories;
}


void Player::issueOrder(string order, string details)
{
//    Order* o = new Order(order, details);
//    orderList->add(o);
}

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

//Goes through all the orders that are in the list of orders of a given player
void Player::printOrders()
{
    cout << "\nPlayer: " << name << " Has the following ordered queued\n";
    for(Order* o : orderList->getList())
    {
        cout << *o << "\n";
    }
}
