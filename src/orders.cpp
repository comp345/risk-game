#include <iostream>
#include <vector>
#include <string>
#include "orders.hpp"

using namespace std;


// Implementation of Orders
Order::Order() : command(""), details("")
{
}
Order::Order(string ordercommand) : command(ordercommand), details("no details")
{
}
Order& Order::operator= (const Order &o)
{
    // self-assignment guard
    if (this == &o)
        return *this;
    // copy every private data members (to do)
    command = o.command;
    details = o.details;

    return *this;
}
ostream& operator<<(ostream &out, const Order &o)
{
    string command = o.command;
    string details = o.details;
    // insert every data field (to do)
    out << "{ ostream object: Command type(" << command << "), Details(" << details << ")}";

    return out;
}
bool Order::validate ()
{
    return true;
}
bool Order::execute ()
{
    return true;
}

Deploy::Deploy() : Order("Deploy type")
{
}
Deploy::Deploy(string ordercommand) : Order(ordercommand)
{
}
// Fake validate and execute methods to implement later
bool Deploy::validate() 
{
    cout << "Validate Deploy order.";
    return true;
}
bool Deploy::execute() 
{
    cout << "Execute Deploy order.";
    return true;
}

Advance::Advance() : Order("Advance type")
{
}
Advance::Advance(string ordercommand) : Order(ordercommand)
{
}
// Fake validate and execute methods to implement later
bool Advance::validate() 
{
    cout << "Validate Advance order.";
    return true;
}
bool Advance::execute() 
{
    cout << "Execute Advance order.";
    return true;
}

Bomb::Bomb() : Order("Bomb type")
{
}
Bomb::Bomb(string ordercommand) : Order(ordercommand)
{
}
// Fake validate and execute methods to implement later
bool Bomb::validate() 
{
    cout << "Validate Bomb order.";
    return true;
}
bool Bomb::execute() 
{
    cout << "Execute Bomb order.";
    return true;
}

Blockade::Blockade() : Order("Blockade type")
{
}
Blockade::Blockade(string ordercommand) : Order(ordercommand)
{
}
// Fake validate and execute methods to implement later
bool Blockade::validate() 
{
    cout << "Validate Blockade order.";
    return true;
}
bool Blockade::execute() 
{
    cout << "Execute Blockade order.";
    return true;
}

AirLift::AirLift() : Order("Airlift type")
{
}
AirLift::AirLift(string ordercommand) : Order(ordercommand)
{
}
bool AirLift::validate() 
{
    cout << "Validate AirLift order.";
    return true;
}
bool AirLift::execute() 
{
    cout << "Execute AirLift order.";
    return true;
}

Negotiate::Negotiate() : Order("Negotiate type")
{
}
Negotiate::Negotiate(string ordercommand) : Order(ordercommand)
{
}
bool Negotiate::validate() 
{
    cout << "Validate Negotiate order.";
    return true;
}
bool Negotiate::execute() 
{
    cout << "Execute Negotiate order.";
    return true;
}

// Implementation of OrderList
OrderList::OrderList()
{
    list = new vector<Order>;
}

vector<Order> OrderList::getList() 
{ 
        vector<Order> list2 = *list;
        return list2; 
}

void OrderList::setList(vector<Order> &olist)
{
    vector<Order> newList = olist; // copy the original list into new object
    list = &newList;
}

OrderList& OrderList::operator=(const OrderList& o) 
{
    if (this == &o)
        return *this;
    this->list = o.list;
    return *this;
}

ostream& operator<<(ostream& out, const OrderList& ol) 
{
    vector<Order> copyList = *(ol.list); // note: cannot use ol.getList() -> non-const functions cannot be called by a const object/reference
    out << "OrderList: {";
    for (vector<Order>::iterator it = copyList.begin(); it != copyList.end(); ++it)
    {
        out << " "
             << (it)->getCommand();
    }
    out << "}";
    return out;
}

void OrderList::add(Order o)
{
    list->push_back(o);
}

void OrderList::remove(int i)
{
    list->erase(list->begin() + i);
}

void OrderList::move(int initPosition, int newPosition)
{
    // validate positions (OutOfBound or if init == new)
    if (initPosition < 0 || initPosition > list->size() - 1 || newPosition < 0 || newPosition > list->size() - 1 || initPosition == newPosition)
        throw std::out_of_range("Exception from OrderList::move. Invalid position(s).\n");
    
    Order o = *(list->begin() + initPosition); // get iterator/node containing the target order
    list->erase(list->begin() + initPosition); // erase from the initposition
    list->insert(list->begin() + newPosition, o); // insert it back at newposition
}

void OrderList::printList()
{
    cout << "Printing an order list!";
    for (vector<Order>::iterator it = list->begin(); it != list->end(); ++it)
    {
        cout << " "
             << (it)->getCommand();
             // << *it;
    }
    cout << "\n";
}