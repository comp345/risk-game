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

    Order *o1 = new Order("First order");
    cout << *o1 << "\n";

    Order *o2 = new Order("Second order");

    Deploy *deploy1 = new Deploy();
    cout << *deploy1 << "\n";

    Advance *advance1 = new Advance();
    cout << *advance1 << "\n";

    Bomb *bomb1 = new Bomb();
    cout << *bomb1 << "\n";

    Blockade *blockade1 = new Blockade();
    cout << *blockade1 << "\n";

    AirLift *airlift1 = new AirLift();
    cout << *airlift1 << "\n";

    Negotiate *negotiate1 = new Negotiate();
    cout << *negotiate1 << "\n";

    // testing the operator=
    // ! REDO: ?? --> THIS CREATES A SHALLOW COPY, REDO!
    *o2 = *o1;
    cout << "\nTesting the assignment operator:\n";
    cout << "Assigning o1 to o2 => "
         << "o1: " << *o1 << ", o2: " << *o2;

    cout << "\nCheck if assignment created a deep copy (not a shallow copy):\n";
    o1->setDetails("New details");
    cout << "o1: " << *o1 << ", o2" << *o2;
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

    // Testing the operator << for OrderList
    cout << "============================================";
    cout << "\nTesting the operator << of OrderList:\n";
    cout << myFirstOrderList
         << "\n";


    // ! Testing OrderList::getList --> does not work with vector<Order*>!
    cout << "============================================";
    vector<Order*>  copyList = myFirstOrderList.getList();
     cout << "\n" << copyList.size();

    cout << "\n...Created a copy of the content of myFirstOrderList.";
    copyList.push_back(new Order("New order to copyList."));

    cout << "...Check if the copyList is a shallow copy of myFirstOrderList's list.\n"
         << "...Yes if Order {\"New order to copyList \"} is added.\n";
    myFirstOrderList.printList();

    // output the copyList content
    cout << "... Outputting content of copyList to compare: \n";
    vector<Order*>::iterator begin = copyList.begin();
    vector<Order*>::iterator end = copyList.end();

    for (vector<Order*>::iterator it = begin; it != end; ++it)
        cout << " " <<(**it).getCommand();
    cout << "\n";


    // Testing the istream operator on Order class
    cout << "\n============================================\n"
     << "User-create a new Order.\n";
//     Order order2; 
//     cin >> order2;
//     cout << "This is the new Order:";
//     cout << order2;
//     cout << "Command: " << order2.getCommand() 
//     << " Details: " << order2.getDetails() << "\n";

//     cout << "\nUser-create a Deploy order\n";
//     Deploy deploy2;
//     cin >> deploy2;
//     cout << "This is the new Deploy:";
//     cout << deploy2;
//     cout << "Command: " << deploy2.getCommand() 
//     << " Details: " << deploy2.getDetails() << "\n";

//     cout << "\nUser-create a Negotiate order\n";
//     Negotiate negotiate2;
//     cin >> negotiate2;
//     cout << "This is the new Negotiate:";
//     cout << negotiate2;
//     cout << "Command: " << negotiate2.getCommand() 
//     << " Details: " << negotiate2.getDetails() << "\n";



    // Test destructors/delete on o1, o2, and the subclasses of Order
    cout << "\n============================================\n";
    cout << "Testing destructor/delete";
    
}