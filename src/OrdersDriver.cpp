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

     Deploy *d1 = new Deploy();
     d1->setDetails("deployig details!");
     cout << *d1 << typeid(*d1).name() << "\n";

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
     cout << "============================================";
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
     myFirstOrderList.add(d1);
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
     d1->execute();
     negotiate1->validate();

     // (deleted test: the istream operator on Order class)

     // Test destructors/delete the subclasses of Order
     cout << "\n============================================\n";
     cout << "Testing destructor/delete\n";
     delete advance1;
     delete airlift1;
     delete d1;
     delete bomb1;
     delete blockade1;
     delete negotiate1;
}

void testOrdersA2()
{
     // ************************************************** //
     //   Initialize parameters for the orders to test...
     // ************************************************** //
     int army = 4;
     Player *p1 = new Player("Hoax", vector<Territory *>(), nullptr, new OrderList());

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();

     // ************************* //
     // Creating a Deploy order   //
     // ************************* //
     Deploy *d1 = new Deploy(army, p1, europeTerritories.at(0));
     Deploy *d1_0 = new Deploy(army, p1, europeTerritories.at(0)); // Creating two Deploy objects as pointer is OK

     cout << "d1: " << d1->getDetails() << endl;
     cout << "d1_0: " << d1_0->getDetails() << endl;

     // Check if d1 and d1_0 point to the same player and territory

     // Deploy d1_1 = Deploy(army, p1, europeTerritories.at(0)); // Creating two Deploy objects as static will give: ERROR for object 0x7f8f76c05af0: pointer being freed was not allocated
     // Deploy d1_2 = Deploy(army, p1, europeTerritories.at(0)); // Error with above!
     // cout << "d1_1: " << d1_1.getDetails() << endl;
     // cout << "d1_2: " << d1_2.getDetails() << endl;

     cout << endl
          << endl;

     // ************************* //
     //   Assignment operator     //
     // ************************* //
     // Deploy *d2 = d1; // WRONG , NOT ASSIGNMENT! Shallow copy: assignment operator not called!
     // Deep copy/Assignment operator
     Deploy *d2;
     *d2 = *d1; // Segmentation error!!
     d2->setDetails(d2->getDetails() + ". ASSIGNMENT!");
     cout << "d2: " << d2->getDetails() << endl;

     cout << endl
          << endl;

     // ************************* //
     //   Copy constructor   //
     // ************************* //

     Deploy *d3 = new Deploy(*d1); // Deep copy
     d3->setDetails(d3->getDetails() + ". COPY!");
     cout << "d3: " << d3->getDetails() << endl;

     cout << endl
          << endl;

     // ************************** //
     //   Default constructor      //
     // ************************** //
     // Deploy *d4 = new Deploy();
     // cout << "d4: " << d4->getDetails() << endl;
     // delete d4;
     // d4 = NULL;

     // ******************************* //
     // Checking for reference equality //
     // ******************************* //
     cout << "Checking for reference equality: " << endl;
     cout << "d1: " << d1->getDetails() << endl;
     cout << "d2 (assignment to d1): " << d2->getDetails() << endl; // shallow copy?
     cout << "d3 (copy of d1): " << d3->getDetails() << endl;       // deep copy?

     cout << endl
          << endl;

     // ***************************************** //
     //        Testing getters and setters      //
     // ***************************************** //
     cout << "Testing getters and setters. Current d1, d2, d3:" << endl;
     cout << "d1 details: " << d1->getDetails() << endl;
     cout << "d1_0 details: " << d1_0->getDetails() << endl; // should contain same Player* as d1
     cout << "d2 details: " << d2->getDetails() << endl;
     cout << "d3 details: " << d3->getDetails() << endl;
     // All the player* should refer to the same player -> ok
     cout << "d1 player: " << d1->getPlayer() << endl;
     cout << "d1_0 player: " << d1_0->getPlayer() << endl;
     cout << "d2 player: " << d2->getPlayer() << endl;
     cout << "d3 player: " << d3->getPlayer() << endl;
     // All the territory* should refer to the same territory -> ok
     cout << "d1 territory: " << d1->getTerritory() << endl;
     cout << "d1_0 territory: " << d1_0->getTerritory() << endl;
     cout << "d2 territory: " << d2->getTerritory() << endl;
     cout << "d3 territory: " << d3->getTerritory() << endl;

     cout << endl;
     cout << "Chanding some data: "
          << "d1: changing player." << endl;
     Player *p2 = new Player("Toast", vector<Territory *>(), nullptr, new OrderList());
     d1->setPlayer(p2);
     cout << "d1 player: " << d1->getPlayer() << endl;
     cout << "d1_0 player: " << d1_0->getPlayer() << endl; // not a shallow copy of d1! is its unique order now
     cout << "d2 player: " << d2->getPlayer() << endl;     // shallow copy of d1,
     cout << "d3 player: " << d3->getPlayer() << endl;

     cout << endl;
     cout << "Chanding some data: "
          << "d1: changing territory." << endl;
     d1->setTerritory(europeTerritories.at(1));
     cout << "d1 player: " << *d1->getTerritory() << endl;
     cout << "d1_0 player: " << *d1_0->getTerritory() << endl;
     cout << "d2 player: " << *d2->getTerritory() << endl;
     cout << "d3 player: " << *d3->getTerritory() << endl;

     // ************************** //
     //        Clean up code       //
     // ************************** //
     // delete p1;
     // p1 = NULL;
     // delete map4;
     // map4 = NULL;

     // delete d1; d1 = NULL;
     // delete d2; d2 = NULL;
     // delete d3; d3 = NULL;
}

void testAssignmentOperator()
{
     // ************************************************** //
     //   Initialize parameters for the orders to test...
     // ************************************************** //
     int army = 4;
     Player *p1 = new Player("Hoax", vector<Territory *>(), nullptr, new OrderList());

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();

     // ************************* //
     // Creating a Deploy order   //
     // ************************* //
     Deploy *d1 = new Deploy(army, p1, europeTerritories.at(0));

     // ************************* //
     //   Assignment operator     //
     // ************************* //
     Deploy *d2 = new Deploy; 
          // The pointer d2 needs to be init with new, else we cannot use the assignment operator!
          // operator= works only on initialized object
     *d2 = *d1;
     cout << d2->getDetails();

     // ********** //
     //   Cleanup  //
     // ********** //
     delete d1;
     delete d2;
}