#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Orders.hpp"
#include "Card.h"
#include "Map.h"

class Territory;
class Hand;

using namespace std;

class Player {
public:
    Player();

    Player(const Player &); //copy constructor
    Player(string);
    Player(string, vector<Territory *>, Hand *, OrderList *);

    ~Player(); //destructor
    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(string, string);

    void issueOrder(Order *o);

    void printOrders();

    // Getters
    vector<Territory *> getTerritories();

    string getName();

    Hand *getHand();

    OrderList *getOrderList();

    void setTerritories(vector<Territory *> vector1);

    void setCards(Hand *pHand);

    //operator overloading
    //assignment operator overloading
    void operator=(const Player& p);
    //stream insertion operator overloading
    friend ostream& operator<<(ostream& out, const Player& p);
    friend istream& operator>>(istream& in, Player& p);

private:
    string name;
    vector<Territory *> territories;
    Hand *hand;
    OrderList *orderList;
};