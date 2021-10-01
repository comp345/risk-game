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
    // Test stream insertion operator on Order object and all its subtypes
    cout << "Testing the stream insertion operators for each Order type/subtype: \n";

    Order o1 = Order("First order");
    cout << o1 << "\n";

    Order o2 = Order("Second order");

    Deploy deploy1 = Deploy();
    cout << deploy1 << "\n";

    Advance advance1 = Advance();
    cout << advance1 << "\n";

    Bomb bomb1 = Bomb();
    cout << bomb1 << "\n";

    Blockade blockade1 = Blockade();
    cout << blockade1 << "\n";

    AirLift airlift1 = AirLift();
    cout << airlift1 << "\n";

    Negotiate negotiate1 = Negotiate();
    cout << negotiate1 << "\n";

    // testing the operator=
    o2 = o1;
    cout << "\nTesting the assignment operator:\n";
    cout << "Assigning o1 to o2 => " << "o1: " << o1 << ", o2: " << o2;
    
    cout << "\nCheck if assignment created a deep copy (not a shallow copy):\n";
    o1.setDetails("New details");
    cout << "o1: " << o1 << ", o2" << o2 ;
    cout << "\n";

    // create OrderList
    OrderList myFirstOrderList;

    // testing adding orders (in alphabetical order) to end of list
    cout << "============================================" 
         << "\nAdding each type of Order in the OrderList: \n";

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
    cout << "============================================" 
         << "\nTesting moving an order in the list: \n";
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
    cout << "============================================" 
         << "\nTesting removing an order from the list: \n";
    myFirstOrderList.remove(4);
    myFirstOrderList.printList();
}