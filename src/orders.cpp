#include <iostream>
#include <vector>
#include <string>
#include "orders.hpp"

using namespace std;


// Implementation of Orders
Order::Order() : name("")
{
}
Order::Order(string orderName) : name(orderName)
{
}
Deploy::Deploy() : Order("Deploy type")
{
}
Deploy::Deploy(string orderName) : Order(orderName)
{
}
Advance::Advance() : Order("Advance type")
{
}
Advance::Advance(string orderName) : Order(orderName)
{
}
Bomb::Bomb() : Order("Bomb type")
{
}
Bomb::Bomb(string orderName) : Order(orderName)
{
}
Blockade::Blockade() : Order("Blockade type")
{
}
Blockade::Blockade(string orderName) : Order(orderName)
{
}
AirLift::AirLift() : Order("Airlift type")
{
}
AirLift::AirLift(string orderName) : Order(orderName)
{
}
Negotiate::Negotiate() : Order("Negotiate type")
{
}
Negotiate::Negotiate(string orderName) : Order(orderName)
{
}

// Implementation of OrderList
OrderList::OrderList()
{
    list = new vector<Order>;
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

    // get iterator/node containing the target order
    Order o = *(list->begin() + initPosition);
    // erase from the initposition
    list->erase(list->begin() + initPosition);
    // insert it back at newposition
    list->insert(list->begin() + newPosition, o);
}
void OrderList::printList()
{
    cout << "Printing an order list!";
    for (vector<Order>::iterator it = list->begin(); it != list->end(); ++it)
    {
        cout << " "
             << (it)->getName();
    }
    cout << "\n";
}