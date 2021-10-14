#include <iostream>
#include <vector>
#include "Orders.hpp"

using namespace std;

// Implementation of Orders
Order::Order() : command(""), details("")
{
}
Order::Order(string ordercommand, string orderdetails) : command(ordercommand), details(orderdetails)
{
}
Order::Order(const Order &o)
{
    command = o.command;
    details = o.details;
}
Order &Order::operator=(const Order &o)
{
    // self-assignment guard
    if (this == &o)
        return *this;
    // copy every private data members (to do)
    command = o.command;
    details = o.details;

    return *this;
}
ostream &operator<<(ostream &out, const Order &o)
{
    string command = o.command;
    string details = o.details;
    // insert every data field (to do)
    out << "{ Order object: Command type(" << command << "), Details(" << details << ")}";

    return out;
}
istream &operator>>(istream &in, Order &o)
{
    // Make user enter every data member of the Order
    cout << "Enter the command type for this new Order.\n";

    bool invalidOrderType = true;
    while (invalidOrderType)
    {
        cout << "Chose a valid command type between advance, airlift, bomb, blockade, deploy, or negotiate (lowercase) :\n";
        string userChosenOrder;
        in >> userChosenOrder;
        if (userChosenOrder.compare("advance") == 0)
        {
            o.command = "Advance type";
            invalidOrderType = false;
            // Below: note for future implementation
            // string command = "Advance type";
            // cout << "Enter details: ";
            // string details;
            // cin >> details;
            // o = Advance(command, details);
            // invalidOrderType = false;
        }
        else if (userChosenOrder.compare("airlift") == 0)
        {
            o.command = "AirLift type";
            invalidOrderType = false;
        }
        else if (userChosenOrder.compare("bomb") == 0)
        {
            o.command = "Bomb type";
            invalidOrderType = false;
        }
        else if (userChosenOrder.compare("deploy") == 0)
        {
            o.command = "Deploy type";
            invalidOrderType = false;
        }
        else if (userChosenOrder.compare("blockade") == 0)
        {
            o.command = "Blockade type";
            invalidOrderType = false;
        }
        else if (userChosenOrder.compare("negotiate") == 0)
        {
            o.command = "Negotiate type";
            invalidOrderType = false;
        } else 
        {
            // continue loop until valid order type (command) entered
        }
    }

    cout << "Details: \n";
    in >> o.details;
    
    // ... Add future data member
    // in >> o.player
    // in >> o.territory

    return in;
}
Order* Order::getOrder()
{
    return this;
}
string Order::getCommand()
{
    return command;
}
void Order::setCommand(std::string ordercommand)
{
    command = ordercommand;
}
std::string Order::getDetails()
{
    return details;
}
void Order::setDetails(std::string orderDetails)
{
    details = orderDetails;
}

//TODO: implement these
//  bool Order::validate()
//  {
//      return true;
//  }
//  bool Order::execute()
//  {
//      return true;
//  }

Deploy::Deploy() : Order("Deploy type", "")
{
}
Deploy::Deploy(string orderdetails) : Order("Deploy type", orderdetails)
{
}
Deploy::Deploy(const Deploy &d)
{
    Deploy cpyDeploy = d;
    setCommand(cpyDeploy.getCommand());
    setDetails(cpyDeploy.getDetails());
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

Advance::Advance() : Order("Advance type", "")
{
}
Advance::Advance(string orderdetails) : Order("Advance type", orderdetails)
{
}
Advance::Advance(const Advance &a)
{
    Advance cpyAdvance = a;
    setCommand(cpyAdvance.getCommand());
    setDetails(cpyAdvance.getDetails());
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

Bomb::Bomb() : Order("Bomb type", "")
{
}
Bomb::Bomb(string orderdetails) : Order("Bomb type", orderdetails)
{
}
Bomb::Bomb(const Bomb &b)
{
    Bomb cpyBomb = b;
    setCommand(cpyBomb.getCommand());
    setDetails(cpyBomb.getDetails());
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

Blockade::Blockade() : Order("Blockade type", "")
{
}
Blockade::Blockade(string orderdetails) : Order("Blockade type", orderdetails)
{
}
Blockade::Blockade(const Blockade &b)
{
    Blockade cpyBlockade = b;
    setCommand(cpyBlockade.getCommand());
    setDetails(cpyBlockade.getDetails());
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

AirLift::AirLift() : Order("Airlift type", "")
{
}
AirLift::AirLift(string orderdetails) : Order("AirLift type", orderdetails)
{
}
AirLift::AirLift(const AirLift &a)
{
    AirLift cpyAirLift = a;
    setCommand(cpyAirLift.getCommand());
    setDetails(cpyAirLift.getDetails());
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

Negotiate::Negotiate() : Order("Negotiate type", "")
{
}
Negotiate::Negotiate(string orderdetails) : Order("Negotiate type", orderdetails)
{
}
Negotiate::Negotiate(const Negotiate &n)
{
    Negotiate cpyNegotiate = n;
    setCommand(cpyNegotiate.getCommand());
    setDetails(cpyNegotiate.getDetails());
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
    list = vector<Order *>();
}
// Copy constructor of OrderList
OrderList::OrderList(const OrderList &ol)
{
    list = ol.list;
}
// returns a deep copy of OrderList's list (vector of pointers to deep copies of Orders)
vector<Order *> OrderList ::getList()
{
    vector<Order *> copyList = vector<Order *>();

    for (int i = 0; i < list.size(); i++)
    {
        Order *ptrOrder = *(list.begin() + i);
        copyList.push_back(ptrOrder);
    }

    return copyList;
}

void OrderList::setList(vector<Order *> olist)
{
    list = olist;
}

OrderList& OrderList::operator=(const OrderList &o)
{
    if (this == &o)
        return *this;
    this->list = o.list;
    return *this;
}

ostream &operator<<(ostream &out, const OrderList &ol)
{
    vector<Order *> copyList = ol.list; // note: cannot use ol.getList() -> non-const functions cannot be called by a const object/reference
    out << "OrderList: {";
    for (vector<Order *>::iterator it = copyList.begin(); it != copyList.end(); ++it)
    {
        out << " "
            << (**it).getCommand();
    }
    out << "}";
    return out;
}

void OrderList::add(Order *o)
{
    list.push_back(o);
}

void OrderList::remove(int i)
{
    list.erase(list.begin() + i);
}

void OrderList::move(int initPosition, int newPosition)
{
    // validate positions (OutOfBound or if init == new)
    if (initPosition < 0 || initPosition > list.size() - 1 || newPosition < 0 || newPosition > list.size() - 1 || initPosition == newPosition)
        throw std::out_of_range("Exception from OrderList::move. Invalid position(s).\n");

    Order *o = *(list.begin() + initPosition);  // get iterator/node (iterator is a ptr?) containing the target order ptr
    list.erase(list.begin() + initPosition);    // erase from the initposition
    list.insert(list.begin() + newPosition, o); // insert it back at newposition
}

void OrderList::printList()
{
    cout << "Printing an order list!";
    for (vector<Order *>::iterator it = list.begin(); it != list.end(); ++it)
    {
        cout << " "
             << (**it).getCommand();
    }
    cout << "\n";
}