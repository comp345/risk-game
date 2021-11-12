#pragma once
#include <vector>
#include <string>
#include <iostream>
// #include "Player.h"
#include "Map.h"
#include "LoggingObserver.h"

// To implement for each Order class/subclass:
// - Player ptr
// - Territory ptr
// - Armies number data member (Deploy, Advance) ?

class OrderList;
class Order;
class Territory;
class Player;

void testOrdersLink();

// The Order class is the base class for Advance, AirLift, Bomb, Blockade, Deploy, Negotiate
// implemented as a pure virtual class to prevent object slicing when using polymorphism with vector
class Order : public ILoggable, public Subject
{
private:
    // name of the order. Tool to debug. To delete later
    std::string command; // Ex. Deploy, Advance, ...

    // standin details string. to delete when Orders are completely implemented
    std::string details; // Ex. Deploy 5 armies to France

public:
    Order();
    // Do not use (A1 legacy)
    Order(std::string command, std::string details);
    Order(const Order &o);
    // virtual ~Order(); // Destructor to implement when ptr data members are added

    Order &operator=(const Order &o);
    friend std::ostream &operator<<(std::ostream &out, const Order &o);
    friend std::istream &operator>>(std::istream &in, Order &o);

    Order *getOrder();
    std::string getCommand() const;
    void setCommand(std::string ordercommand);
    std::string getDetails() const;
    void setDetails(std::string orderDetails);

    // To implement
    virtual bool validate() = 0;
    virtual bool execute() = 0;
};

class Deploy : public Order
{
private:
    int armiesToMove;
    Player *playerDeploying;
    Territory *territoryTarget;

public:
    Deploy();
    Deploy(std::string details); // don't use
    Deploy(int armies, Player *player, Territory *territory);
    Deploy(const Deploy &d); // Deep copy. Use for value semantics (pass/return by value). Don't use to create orders to execute
    ~Deploy();
    // Shallow copy. Reference semantics
    Deploy &operator=(const Deploy &d);

    // friend std::ostream& operator<<(std::ostream& out, const Deploy& d);

    int getArmies() const;
    Player *getPlayer() const;
    Territory *getTerritory() const;
    void setArmies(int armies);
    void setPlayer(Player *p);
    void setTerritory(Territory *t);

    bool validate();
    bool execute();
    string stringToLog() override;
};

class Advance : public Order
{
private:
    int armiesToMove;
    Player* playerAdvancing;
    Territory* territorySource;
    Territory* territoryTarget;
public:
    Advance();
    Advance(std::string details); // don't use
    Advance(int armies, Player* player, Territory* src, Territory* target);
    Advance(const Advance &a);

    int getArmies() const;
    Player *getPlayer() const;
    Territory *getTerritorySource() const;
    Territory *getTerritoryTarget() const;
    void setArmies(int armies);
    void setPlayer(Player *p);
    void setTerritorySource(Territory *t);
    void setTerritoryTarget(Territory *t);

    bool validate();
    bool execute();
    string stringToLog() override;
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(std::string details);
    // Copu constructor to-do
    Bomb(const Bomb &b);

    bool validate();
    bool execute();
    string stringToLog() override;
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(std::string details);
    Blockade(const Blockade &b);

    bool validate();
    bool execute();
    string stringToLog() override;
};
class AirLift : public Order
{
public:
    AirLift();
    AirLift(std::string details);
    AirLift(const AirLift &a);

    bool validate();
    bool execute();
    string stringToLog() override;
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(std::string details);
    // Copy constructor to-do
    Negotiate(const Negotiate &n);

    bool validate();
    bool execute();
    string stringToLog() override;
};

class OrderList : public ILoggable, public Subject
{
public:
    OrderList();
    OrderList(const OrderList &ol);
    ~OrderList(); // no need to explicitely call destructor

    OrderList &operator=(const OrderList &o);

    friend std::ostream &operator<<(std::ostream &out, const OrderList &ol);
    friend std::istream &operator>>(std::istream &in, OrderList &ol);

    // adds an order ptr at the end of the orderlist
    void add(Order *o);

    // remove an order ptr by its position (positions start at 0).
    void remove(int i);

    // move order from init to new position. Throws out_of_range exception.
    void move(int initPosition, int newPosition);

    // prints every order's command on the console.
    void printList();

    // returns a deep copy of the list (tested)
    std::vector<Order *> getList();

    void setList(std::vector<Order *> list);

    string stringToLog() override;

private:
    std::vector<Order *> list;
};

// Test function (to delete)
void testOrdersDriver();

void testOrdersA2();

void testAssignmentOperator();

void testDeployExec();
