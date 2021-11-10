#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

using namespace std;

void testOrdersLink()
{
     cout << "Successfully linked orders.cpp and orders.hpp to main\n";
}

void testOrdersDriver()
{
     cout << "Testing the stream insertion operators for each Order type/subtype: \n";

     Deploy *deploy1 = new Deploy();
     deploy1->setDetails("deployig details!");
     cout << *deploy1 << typeid(*deploy1).name() << "\n";

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
     cout << "============================================" ;
     AirLift *a1 = new AirLift("First order");
     cout << *a1 << "\n";

     AirLift *a2 = new AirLift("Second order");
     cout << "\nTesting the assignment operator (inherited from Order class) with AirLift:\n";
     *a2 = *a1;
     cout << "Assigning a1 to a2 => "
          << "a1: " << *a1 << ", a2: " << *a2;

     cout << "\nCheck if assignment created a deep copy (not a shallow copy):\n";
     a1->setCommand("Update command");
     a1->setDetails("Update details");
     cout << "a1: " << *a1 << ", a2: " << *a2;
     cout << "\n";

     // create OrderList
     OrderList myFirstOrderList;

     // testing adding orders (in alphabetical order) to end of list
     cout << "============================================"
          << "\nAdding each ptr to Order in the OrderList: \n";

     myFirstOrderList.add(advance1);
     myFirstOrderList.add(airlift1);
     myFirstOrderList.add(blockade1);
     myFirstOrderList.add(bomb1);
     myFirstOrderList.add(deploy1);
     myFirstOrderList.add(negotiate1);

     myFirstOrderList.printList();
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
          return;
     }


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

     // Testing OrderList::getList
     cout << "============================================";
     vector<Order *> copyList = myFirstOrderList.getList();

     cout << "\n...Created a copy of the content of myFirstOrderList.";
     copyList.push_back(new Deploy("new details for copyList"));

     cout << "...Check if the copyList is a shallow copy of myFirstOrderList's list.\n"
          << "-> Yes if Order {\"New order to copyList \"} is added ONLY to myFirstOrderList.\n";
     myFirstOrderList.printList();

     // output the copyList content
     cout << "... Outputting content of copyList to compare: \n";
     vector<Order *>::iterator begin = copyList.begin();
     vector<Order *>::iterator end = copyList.end();

     for (vector<Order *>::iterator it = begin; it != end; ++it)
          cout << " " << (**it).getCommand();
     cout << "\n";

     // Testing OrderList::setList
     cout << "======================================\n";
     cout << "Testing OrderList::setList. This method copies the Vector<Order*> copyList passed as argument to setList.\n";
     OrderList UpdatedFirstList;
     UpdatedFirstList.setList(copyList);
     cout << "UpdateFirstList: " << UpdatedFirstList << "\n";

     // Testing assignment operator= from OrderList by creating a duplicate OrderList
     cout << "============================================\n";
     cout << "Testing assignment operator= from OrderList by creating a duplicate OrderList\n";
     OrderList mySecondOrderList;
     mySecondOrderList = myFirstOrderList;
     cout << "First OrderList: " << myFirstOrderList << "\n";
     cout << "Second OrderList: " << mySecondOrderList << "\n";
     cout << "...Adding Order ptr to Second OrderList to verify that it is a deep copy\n";
     mySecondOrderList.add(new Advance("Test Second OrderList"));
     cout << "... Printing Second OrderList: " << mySecondOrderList << "\n";
     cout << "... Printing First OrderList: " << myFirstOrderList << "\n";

     // Testing the OrderList copy constructor
     cout << "============================================\n";
     cout << "Testing OrderList copy constructor\n";
     OrderList myThirdOrderList = OrderList(myFirstOrderList);
     cout << "First OrderList: " << myFirstOrderList << "\n";
     cout << "Third OrderList: " << myThirdOrderList << "\n";
     cout << "Updating the Third OrderList (adding new order)\n";
     myThirdOrderList.add(new Bomb("Test Third Orderlist"));
     cout << "First OrderList: " << myFirstOrderList << "\n";
     cout << "Third OrderList: " << myThirdOrderList << "\n";

     cout << "===============================================\n";
     cout << "\nCheck if the copy constructor preserved the static classes of the objects: \n";
     cout << myFirstOrderList.getList().at(0)->getCommand() << ":"
          << myFirstOrderList.getList().at(0)->execute() << "\n";
     cout << myFirstOrderList.getList().at(1)->getCommand() << ":"
          << myFirstOrderList.getList().at(1)->execute() << "\n";
     cout << myFirstOrderList.getList().at(2)->getCommand() << ":"
          << myFirstOrderList.getList().at(2)->execute() << "\n";
     cout << myFirstOrderList.getList().at(3)->getCommand() << ":"
          << myFirstOrderList.getList().at(3)->execute() << "\n";
     cout << myFirstOrderList.getList().at(4)->getCommand() << ":"
          << myFirstOrderList.getList().at(4)->execute() << "\n";

     // Testing validate() and execute()
     cout << "\n============================================\n"
          << "Testing validate() and execute().\n";
     deploy1->execute();
     negotiate1->validate();

     // (deleted test: the istream operator on Order class)

     // Test destructors/delete the subclasses of Order
     cout << "\n============================================\n";
     cout << "Testing destructor/delete\n";
     delete advance1;
     delete airlift1;
     delete deploy1;
     delete bomb1;
     delete blockade1;
     delete negotiate1;
}

// int main()
// {
//      testOrdersDriver();
//      return 0;
// }