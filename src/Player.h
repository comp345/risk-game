#pragma once

#include <string>
#include <vector>
#include <iostream>

class Territory;
class Hand;
class Order;
class OrderList;

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
    Player& operator=(const Player& p);
    //stream insertion operator overloading
    friend ostream& operator<<(ostream& out, const Player& p);
    friend istream& operator>>(istream& in, Player& p);
    
    
    int reinforcementPool;
    
private:
    string name;
    vector<Territory *> territories;
    Hand *hand;
    OrderList *orderList;
    
};