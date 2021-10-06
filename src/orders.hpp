#include <vector>
#include <string>
#include <iostream>

// Destructors to implement!!

void testOrdersLink();

class Order
{
private:
    // command attribute to debug. to delete?
    std::string command; // Ex. Deploy, Advance, ...
    // standin details string. to delete when Orders are completely implemented
    std::string details; // Ex. Deploy 5 armies to France

public:
    Order();
    Order(std::string command);
    // Copy constructor (to-do)
    // Order(const Order &o);
    
    
    Order &operator=(const Order &o);
    friend std::ostream &operator<<(std::ostream &out, const Order &o);
    friend std::istream &operator>>(std::istream &in, Order& o);

    std::string getCommand();
    void setCommand(std::string ordercommand);
    std::string getDetails();
    void setDetails(std::string orderDetails);
    
    // To implement
    bool validate();
    bool execute();
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(std::string command);
    // Copy constructor to-do
    // Deploy(const Deploy &d);
    bool validate ();
    bool execute ();
};

class Advance : public Order
{
public:
    Advance();
    Advance(std::string command);
    // Copy constructor to-do
    // Advance(const Advance &a);
    bool validate ();
    bool execute ();
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(std::string command);
    // Copu constructor to-do
    // Bomb(const Bomb &b);
    bool validate ();
    bool execute ();
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(std::string command);
    // Copy constructor to-do
    // Blockade(Blockade &b);
    bool validate ();
    bool execute ();
};
class AirLift : public Order
{
public:
    AirLift();
    AirLift(std::string command);
    // Copy constructor to-do
    // AirLift(AirLift &a);
    bool validate ();
    bool execute ();
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(std::string command);
    // Copy constructor to-do
    // Negotiate(Negotiate &n);
    bool validate ();
    bool execute ();
};

class OrderList
{
public:
    OrderList();
    // Copy constructor to-do
    // OrderList(const OrderList& ol);

    OrderList &operator=(const OrderList &o);

    friend std::ostream &operator<<(std::ostream &out, const OrderList &ol);
    friend std::istream &operator>>(std::istream &in, OrderList& ol);

    // adds an order ptr at the end of the orderlist
    void add(Order *o);
    
    // remove an order ptr by its position (positions start at 0).
    // return the order ptr (?)
    void remove(int i);
    
    // move order from init to new position. Throws out_of_range exception.
    void move(int initPosition, int newPosition);
    
    // prints every order's command on the console.
    void printList();

    // returns a deep copy of the list (tested)
    std::vector<Order*> getList();
    
    // to be tested
    void setList(std::vector<Order*> list);

private:
    std::vector<Order*> list;
};

// Test function (to delete)
void testOrdersDriver();
