#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
    plArmies=0;
    territories = vector<Territory *>();
    hand = new Hand();//cards in players hand
    orderList = new OrderList();
}

Player::Player(string n)
{
    this->name = n;
    this->plArmies;
    this->hand = new Hand();
    this->orderList = new OrderList();
}

//parametrized constructor
Player::Player(int armies, string plName, vector<Territory*> t, Hand* h, OrderList* o)
{
    this->plArmies=armies;
    this->name = plName;
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
    for (Territory* t : territories) {
        delete t;
        t = nullptr;
    }
    //territories.clear();
    delete orderList;
    orderList = nullptr;
    delete hand;
    hand = nullptr;
    plArmies=0;
    name="";
}

//operator overloading
//assignment operator overloading
Player& Player::operator=(const Player& p) {
//    if (this == &p)
//        return *this;

    territories = p.territories;
    hand = new Hand(*(p.hand));
    orderList = new OrderList(*(p.orderList));
    plArmies=p.plArmies;
    name=p.name;
    return *this;
}

//stream insertion operator overloading
ostream& operator<<(ostream& out, const Player& p) {
    out<<"\nName of player: "<<p.name<<endl;

    out<<"Army of player: "<<p.plArmies<<endl;

    out << "Territories: (should print if assigned!)" << endl;
    for (Territory* t : p.territories) {
        out << *t << endl;
    }
    out << "Orders: should be printing here (for debugging)\n";
    if (p.orderList != nullptr) {
        for (Order* o : p.orderList->getList()) {
            out << "Orders: " << *o << endl;
        }
    }

    else {
        out << "\nOrders not initialized";
    }

    if (p.hand != nullptr) {
        for (Card* c : p.hand->getCards()) {
            out << "\nCard: " << *c << endl;
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

Hand* Player::getHand() {
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

void Player::setTerritories(vector<Territory *> t1) {
    //territories = terr;
    for(Territory* t: t1){
        this->territories.push_back(t);
    }
}

void Player::setCards(Hand *pHand) {
    hand = pHand;
}
void Player::setPlName(string plName) {
    name=plName;
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
int Player::getPlArmies() {
    return plArmies;
}
void Player::setPlArmies(int armies) {
    plArmies=armies;
}