#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>
// #include "LoggingObserver.h"
// #include "Orders.h"
// #include "Card.h"
// #include "Map.h"

class Territory;
class Hand;
class Order;
class OrderList;

using namespace std;

struct compareArmySize
{
    bool operator()(Territory const* t1, Territory const* t2);
};

class Player
{
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
    Player &operator=(const Player &p);
    //stream insertion operator overloading
    friend ostream &operator<<(ostream &out, const Player &p);
    friend istream &operator>>(istream &in, Player &p);

    int getTerritorySize();
    int getPrevTerritorySize();
    void setPrevTerritorySize();

    

    void addToPriorityAttack(Territory *toAdd);
    void addToPriorityDefend(Territory *toAdd);
    Territory* popPriorityDefend();

    priority_queue<Territory *, vector<Territory *>, compareArmySize> getPriorityAttacking();
    priority_queue<Territory *, vector<Territory *>, compareArmySize> getPriorityDefending();

    bool isDoneIssuing();
    void toggleDoneIssuing();

    int getReinforcementPool();
    void setReinforcementPool(int val);

private:
    int reinforcementPool;
    int prevTerritorySize;
    priority_queue<Territory *, vector<Territory *>, compareArmySize> priorityAttacking;
    priority_queue<Territory *, vector<Territory *>, compareArmySize> priorityDefending;

    string name;
    vector<Territory *> territories;
    Hand *hand;
    OrderList *orderList;

    bool doneIssuing;
};