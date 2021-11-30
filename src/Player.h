#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

class Territory;

class Hand;

class Order;

class OrderList;

class PlayerStrategy;

using namespace std;

struct compareArmySize
{
    bool operator()(Territory const *t1, Territory const *t2);
};

class Player
{
public:
    Player();

    Player(const Player &); //copy constructor
    Player(string);

    Player(int, string, vector<Territory *>, Hand *, OrderList *);

    Player(string plName, vector<Territory *> t, Hand *h, OrderList *o);

    ~Player(); //destructor
    virtual vector<Territory *> toAttack();

    virtual vector<Territory *> toDefend();

    void issueOrder(); // A3 

    void issueOrder(string, string);

    void issueOrder(Order *o); // A2

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
    bool isNegotiating(Player *p);
    void addNegotiatingWith(Player *p);
    void removeNegotiatingWith(Player *p);
    vector<Player *> getNegotiatingWith() const;
    void removeAllNegotiation();
    PlayerStrategy *getPlayerStrategy();
    void setPlayerStrategy(PlayerStrategy *ps);

private:
    int reinforcementPool;
    int prevTerritorySize;
    priority_queue<Territory *, vector<Territory *>, compareArmySize> priorityAttacking;
    priority_queue<Territory *, vector<Territory *>, compareArmySize> priorityDefending;

    string name;
    vector<Territory *> territories;
    Hand *hand;
    OrderList *orderList;
    PlayerStrategy *ps;

    bool doneIssuing;
    int plArmies;

    // implementation of Negotiate order
    vector<Player *> negotiatingWith;
};