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
    delete hand;
}

void Player::toAttack()
{
    for (int i = 0; i < territories.size(); i++)
    {
        cout << territories[i] << "";
    }

}

void Player::toDefend()
{
    for (int i = 0; i < territories.size(); i++)
    {
        cout << territories[i] << "";
    }
}


void Player::issueOrder(string order, string details)
{
    Order* o = new Order(order, details);
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