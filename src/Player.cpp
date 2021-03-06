#include "Player.h"
#include "Card.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include "Orders.h"
#include "Map.h"
#include "PlayerStrategies.h"  
#include "GameEngine.h"  

using namespace std;

extern void dprint(string message, section option);

bool compareArmySize::operator()(Territory const *t1, Territory const *t2)
{
    // return "true" if "p1" is ordered
    // before "p2", for example:

    // For aggresive player we need to only select the strongest territories:
    // For simplification, we assume aggressive players deploy/advance toward their strongest territory, but
    // also attacks strongest enemy territories!
    if (t1->owner->getPlayerStrategy()->strategyName() == "Aggressive strategy")
    {
        return t1->numArmies < t2->numArmies;
    }
    else
        return t1->numArmies > t2->numArmies; // Default, used in A2
}

Player::Player()
{
    reinforcementPool = 0;
    territories = vector<Territory *>();
    hand = new Hand();
    orderList = new OrderList();
    this->prevTerritorySize = 0;
    this->doneIssuing = false;
    this->doneDeploying = false;
    priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    priorityDefending = priority_queue<Territory *, vector<Territory *>, compareArmySize>();

    // Implementing Negotiate order
    negotiatingWith = vector<Player *>();

    // From a3_strategy
    this->playerStrategy = new NormalPlayerStrategy(this);
}

Player::Player(string n)
{
    this->name = n;
    this->reinforcementPool = 0;
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->doneIssuing = false;
    this->doneDeploying = false;
    this->priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    this->priorityDefending = priority_queue<Territory *, vector<Territory *>, compareArmySize>();

    // Implementing Negotiate order
    negotiatingWith = vector<Player *>();

    // a3_strategy
    this->playerStrategy = new NormalPlayerStrategy(this);
}

// parametrized constructor
Player::Player(string plName, vector<Territory *> t, Hand *h, OrderList *o)
{
    this->name = plName;
    this->territories = t;
    this->hand = h;
    this->orderList = o;
    this->doneIssuing = false;
    this->doneDeploying = false;
    this->prevTerritorySize = territories.size();
    this->priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    this->priorityDefending = priority_queue<Territory *, vector<Territory *>, compareArmySize>();

    // Implementing Negotiate order
    negotiatingWith = vector<Player *>();

    // Link player with strategy
    this->playerStrategy = new NormalPlayerStrategy(this);
}

// parametrized constructor
Player::Player(int armies, string plName, vector<Territory *> t, Hand *h, OrderList *o)
{
    this->reinforcementPool = armies;
    this->name = plName;
    this->territories = t;
    this->hand = h;
    this->orderList = o;
    this->doneIssuing = false;
    this->doneDeploying = false;
    this->prevTerritorySize = territories.size();
    this->priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    this->priorityDefending = priority_queue<Territory *, vector<Territory *>, compareArmySize>();

    // Implementing Negotiate order
    negotiatingWith = vector<Player *>();
    // Link player with strategy
    this->playerStrategy = new NormalPlayerStrategy(this);
}

// copy constructor: Deep copy, cannot be used for reference semantic or to
Player::Player(const Player &p)
{
    // cout << "Entering Player::Player(const Player& p)" <<endl;
    this->name = p.name;
    this->territories = p.territories;
    this->hand = new Hand(*p.hand);
    this->doneIssuing = p.doneIssuing;
    this->doneIssuing = p.doneDeploying;
    this->orderList = new OrderList(*p.orderList);
    this->priorityAttacking = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    this->priorityDefending = priority_queue<Territory *, vector<Territory *>, compareArmySize>();
    // cout << "Exiting Player::Player(const Player& p)" <<endl;

    // Implementing Negotiate order
    this->negotiatingWith = p.negotiatingWith;
    // Link player with strategy
    this->playerStrategy = p.playerStrategy;
}

// destructor
Player::~Player()
{
    territories.clear();
    delete orderList;
    orderList = nullptr;
    delete hand;
    hand = nullptr;
    for (auto p : negotiatingWith)
    {
        delete p;
    }
    negotiatingWith.clear();

    //    delete playerStrategy; 
    // gives linkage error Undefined symbols for architecture x86_64:
    //   "__ZN14PlayerStrategyD1Ev", referenced from:
    //       __ZN6PlayerD2Ev in Player.cpp.o
    //       __ZN6PlayerD1Ev in Player.cpp.o

    for (Territory *t : territories)
    {
        delete t;
        t = nullptr;
    }
}

// operator overloading
// assignment operator overloading
//  Noah note for A2: Deep copy
Player &Player::operator=(const Player &p)
{
    if (this == &p)
        return *this;

    territories = p.territories;
    if (hand)
        delete hand;
    if (orderList)
        delete orderList;
    if (!negotiatingWith.empty())
    {
        for (auto n : negotiatingWith)
            delete n;
    }
    negotiatingWith.clear();
    hand = new Hand(*(p.hand));
    orderList = new OrderList(*(p.orderList));
    reinforcementPool = p.reinforcementPool;
    negotiatingWith = p.negotiatingWith;
    name = p.name;
    playerStrategy = p.playerStrategy;
    doneIssuing = p.doneIssuing;
    doneDeploying = p.doneDeploying;
    return *this;
}

// stream insertion operator overloading
ostream &operator<<(ostream &out, const Player &p)
{
    out << "\nName of player: " << p.name << endl;
    out << "Army of player: " << p.reinforcementPool << endl;
    out << "Territories: " << endl;
    for (Territory *t : p.territories)
    {
        out << *t << endl;
    }

    if (p.orderList != nullptr)
    {
        for (Order *o : p.orderList->getList())
        {
            out << "Orders: " << *o << endl;
        }
        out << "Orders should be printing here\n";
    }
    else
    {
        out << "\nOrders not initialized";
    }

    if (p.hand != nullptr)
    {
        for (Card *c : p.hand->getCards())
        {
            out << "\nCard: " << *c << endl;
        }
    }
    else
    {
        out << "\nHand not initialized";
    }

    return out;
}

istream &operator>>(istream &in, Player &p)
{
    in >> p.name;
    return in;
}

// returns a list of territories to attack
vector<Territory *> Player::toAttack()
{
    return getPlayerStrategy()->toAttack();
}

// returns a list of territories to defend
vector<Territory *> Player::toDefend()
{
    return getPlayerStrategy()->toDefend();
}

// A2 Implementation
// adds order to a player's list of orders
void Player::issueOrder(Order *o)
{
    getPlayerStrategy()->issueOrder(o);
}

// TODO = A3: calls the strategy's
void Player::issueOrder()
{
    dprint("Entering... Player::issueOrder()", section::issueOrderFromPlayer);
    this->getPlayerStrategy()->issueOrder();
}

Hand *Player::getHand()
{
    return hand;
}

vector<Territory *> &Player::getTerritories()
{
    return territories;
}

string Player::getName()
{
    return name;
}

OrderList *Player::getOrderList()
{
    return orderList;
}

void Player::setTerritories(vector<Territory *> t1)
{
    territories = t1;
    prevTerritorySize = territories.size();
}

void Player::addTerritories(vector<Territory *> t1)
{
    for (Territory *t : t1)
    {
        this->territories.push_back(t);
    }
}
void Player::addTerritory(Territory *t1)
{
    territories.push_back(t1);
}

void Player::setCards(Hand *pHand)
{
    hand = pHand;
}

void Player::setPlName(string plName)
{
    name = plName;
}

// Goes through all the orders that are in the list of orders of a given player and prints them
void Player::printOrders()
{
    cout << "\nPlayer: " << name << " Has the following ordered queued\n";
    for (Order *o : orderList->getList())
    {
        cout << *o << "\n";
    }
}

int Player::getTerritorySize()
{
    return this->getTerritories().size();
}

int Player::getPrevTerritorySize()
{
    return prevTerritorySize;
}

void Player::setPrevTerritorySize()
{
    prevTerritorySize = territories.size();
}

void Player::addToPriorityAttack(Territory *toAdd)
{
    priorityAttacking.push(toAdd);
}

void Player::addToPriorityDefend(Territory *toAdd)
{
    priorityDefending.push(toAdd);
}

priority_queue<Territory *, vector<Territory *>, compareArmySize> Player::getPriorityAttacking()
{
    return priorityAttacking;
}

priority_queue<Territory *, vector<Territory *>, compareArmySize> Player::getPriorityDefending()
{
    return priorityDefending;
}

bool Player::isDoneIssuing()
{
    return doneIssuing;
}

void Player::toggleDoneIssuing()
{
    if (doneIssuing == true)
        doneIssuing = false;
    else
        doneIssuing = true;
}

void Player::setDoneIssuing(bool flag)
{
    doneIssuing = flag;
}

bool Player::isDoneDeploying()
{
    return doneDeploying;
}

void Player::setDoneDeploying(bool flag)
{
    doneDeploying = flag;
}

int Player::getReinforcementPool()
{
    return reinforcementPool;
}

void Player::setReinforcementPool(int val)
{
    reinforcementPool = val;
}

Territory *Player::popPriorityDefend()
{
    Territory *p = priorityDefending.top();
    priorityDefending.pop();
    return p;
}

Territory *Player::popPriorityAttack()
{
    Territory *p = priorityAttacking.top();
    priorityAttacking.pop();
    return p;
}

// Implementing Negotiate order

bool Player::isNegotiating(Player *p)
{
    // Check if our player is negotiating with the passed player by iterating through the vector
    for (Player *negotiatee : negotiatingWith)
    {
        if (negotiatee == p)
        {
            return true;
        }
    }
    return false;
}
void Player::addNegotiatingWith(Player *p)
{
    negotiatingWith.push_back(p);
}
void Player::removeNegotiatingWith(Player *p)
{
    for (int i = 0; i < negotiatingWith.size(); ++i)
    {
        if (negotiatingWith.at(i) == p)
        {
            negotiatingWith.erase(negotiatingWith.begin() + i);
            return;
        }
    }
}
vector<Player *> Player::getNegotiatingWith() const
{
    return negotiatingWith;
}
// Flush all negotation at the end of ExecuteOrders phase
void Player::removeAllNegotiation()
{
    // empty vector of pointers, don't deallocate the players!
    negotiatingWith.clear();
}
PlayerStrategy *Player::getPlayerStrategy()
{
    return playerStrategy;
}

void Player::setPlayerStrategy(PlayerStrategy *playerStrategy)
{
    this->playerStrategy = playerStrategy;
}
