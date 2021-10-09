#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "orders.hpp"
#include "Card.h"
#include "Map.h"

using namespace std;

class Player {
public:
    Player();

    Player(const Player &); //copy constructor
    Player(string, vector<Territory *>, Hand *, OrderList *);

    ~Player(); //destructor
    void toAttack();

    void toDefend();

    void issueOrder(string, string);

    // Getters
    vector<Territory *> getTerritories();

    string getName();

    Hand *getHand();

    OrderList *getOrderList();

private:
    string name;
    vector<Territory *> territories;
    Hand *hand;
    OrderList *orderList;
};