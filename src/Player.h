#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

class Territory;

class Hand;

class Order;

class OrderList;

using namespace std;

struct compareArmySize {
    bool operator()(Territory const *t1, Territory const *t2);
};

class Player {
public:

    Player();

    Player(const Player &); //copy constructor
    Player(string);

    Player(int, string, vector<Territory *>, Hand *, OrderList *);

    Player(string plName, vector<Territory *> t, Hand *h, OrderList *o);

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

    int getPlArmies();

    void setPlArmies(int armies);

    void setPlName(string plName);

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

    Territory *popPriorityDefend();

    Territory *popPriorityAttack();

    priority_queue<Territory *, vector<Territory *>, compareArmySize> getPriorityAttacking();

    priority_queue<Territory *, vector<Territory *>, compareArmySize> getPriorityDefending();

    bool isDoneIssuing();

    void toggleDoneIssuing();

    int getReinforcementPool();

    void setReinforcementPool(int val);

    void addTerritories(vector<Territory *> t1);

    // implementation of Negotiate order
    bool isNegotiating();
    void setNegotiatingWith(Player * p);
    void removeNegotiatingWith();
    Player * getNegotiatingWith() const;


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
    int plArmies;

    // implementation of Negotiate order
    Player * negotiatingWith; 

};