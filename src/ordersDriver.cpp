#include <iostream>
#include <vector>
#include <string>
#include "orders.hpp"

using namespace std;


void testOrdersLink()
{
    cout << "Successfully linked orders.cpp and orders.hpp to main\n";
}

void testOrdersDriver()
{

    // Testing creation and init of order and their subtypes here
    Order o1 = Order("First order");
    cout << o1.getName()
         << "\n";

    Deploy deploy1 = Deploy();
    cout << deploy1.getName()
         << "\n";

    Advance advance1 = Advance();
    cout << advance1.getName()
         << "\n";

    Bomb bomb1 = Bomb();
    cout << bomb1.getName()
         << "\n";

    Blockade blockade1 = Blockade();
    cout << blockade1.getName()
         << "\n";

    AirLift airlift1 = AirLift();
    cout << airlift1.getName()
         << "\n";

    Negotiate negotiate1 = Negotiate();
    cout << negotiate1.getName()
         << "\n";

    // create OrderList
    OrderList myFirstOrderList;

    // testing adding orders (in alphabetical order) to end of list
    myFirstOrderList.add(advance1);
    myFirstOrderList.add(airlift1);
    myFirstOrderList.add(blockade1);
    myFirstOrderList.add(bomb1);
    myFirstOrderList.add(deploy1);
    myFirstOrderList.add(negotiate1);

    myFirstOrderList.printList();

    // check if we should add orders by pointer/ or directly ...
    // add duplicate
    // myFirstOrderList.add(advance1);

    // move orders
    try
    {
        myFirstOrderList.move(0, 5);
        myFirstOrderList.printList();
    }
    catch (std::out_of_range e)
    {
        cout << e.what()
             << "End program with failure\n";
        return exit(1);
    }

    // check invalid moves (OutOfBound)

    // remove order by position (starting at position 0)
    myFirstOrderList.remove(4);
    myFirstOrderList.printList();
}