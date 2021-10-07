#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "orders.hpp"

using namespace std;

class Player {
    public:
        Player();
        Player(const Player&); //copy constructor
        Player(vector<Territory*> t, Hand* h, OrderList* o); //copy constructor
        ~Player(); //destructor
        void toAttack();
        void toDefend();
        void issueOrder(string);

    private:
        vector<Territory*> territories;
        Hand* hand;
        OrderList* orderList;
};

class Territory {
};

class Hand {
};