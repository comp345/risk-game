#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "Card.h"

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
     Player *p1 = new Player("Hoax");

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();
     Territory *t1 = europeTerritories.at(0);

     // ************************* //
     // Creating a Deploy order   //
     // ************************* //
     // Creating 2 distinct Deploy objects with same parameters should result in orders that execute on same Player and Territory
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
     // Deep copy/Assignment operator: The created Deploy order has a different Player and Territory to original Deploy... wrong
     Deploy *d2 = new Deploy; // Deploy *d2; *d2 = *d1; // -> Error since dereferencing wild pointer
     *d2 = *d1;
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
     cout << "d2 (assignment to d1): " << d2->getDetails() << endl; // now a deep copy! OK
     cout << "d3 (copy of d1): " << d3->getDetails() << endl;       // deep copy? OK

     cout << endl
          << endl;

     // ***************************************** //
     //        Testing getters and setters      //
     // ***************************************** //
     cout << "Testing getters and setters. Current d1, d2, d3:" << endl;
     // Originally passed player p1 and territory england
     cout << "*p1: " << &(*p1) << endl;
     cout << "*t1: " << &(*t1) << endl;
     cout << "*europeTerritories.at(0):  " << &(*europeTerritories.at(0)) << endl;
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
     cout << "d2 player: " << d2->getPlayer() << endl;     // now a deep copy!
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
     // DO NOT create players like that: Player *p1 = new Player("Hoax", vector<Territory *>(), nullptr, nullptr);
     Player *p1 = new Player("Hoax");

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

void testDeployExec()
{
     // ************************************************** //
     //   Initialize parameters for the orders to test...
     // ************************************************** //
     int army = 4;
     Player *p1 = new Player("Hoax");

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();
     Territory *t1 = europeTerritories.at(0);

     // To create a valid territory, need to specify owner and number of armies (if territory is conquered)
     t1->setNumberOfArmies(5);
     t1->setOwner(p1);

     // ************************* //
     // Creating a Deploy order   //
     // ************************* //

     // Creating 2 distinct Deploy objects with same parameters should result in orders that execute on same Player and Territory
     Deploy *d1 = new Deploy(army, p1, t1);
     Deploy *d1_0 = new Deploy(army, p1, t1); // Creating two Deploy objects as pointer is OK

     cout << "===================================" << endl;
     cout << "p1: " << &(*p1) << endl;
     cout << "t1: " << &(*t1) << endl;
     cout << "d1: " << d1->getDetails() << endl
          << "d1.playerDeploying: " << d1->getPlayer() << endl
          << "d1.territoryTarget: " << d1->getTerritory() << endl;

     cout << "Executing Deploy order d1." << endl;
     d1->execute();
     cout << "t1 After d1 execution: " << *t1 << endl;

     cout << "Executing Deploy order d1_0" << endl;
     d1_0->execute();
     cout << "t1 After d1_0 execution: " << *t1 << endl;
}

void testAdvanceExec()
{
     // ************************************************** //
     //   Initialize parameters for the orders to test...
     // ************************************************** //
     Player *p1 = new Player("Hoax");
     Player *p2 = new Player("Toast");

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();
     Territory *t1 = europeTerritories.at(0);
     Territory *t2 = europeTerritories.at(1);
     Territory *t3 = europeTerritories.at(2);
     Territory *t4 = europeTerritories.at(3);

     // To create a valid territory, need to specify owner and number of armies (if territory is conquered)
     t1->setNumberOfArmies(5);
     t1->setOwner(p1);
     t2->setNumberOfArmies(9);
     t2->setOwner(p1);
     t3->setNumberOfArmies(11);
     t3->setOwner(p2);
     t4->setNumberOfArmies(3);
     t4->setOwner(p2);

     // Player Hoax owns England, which has 5 armies
     // Player Hoax owns Scotland, which has 9 armies
     // Player Toast owns Ireland (?), which has 11 armies

     cout << "===================================" << endl
          << endl;

     cout << "Displaying players and territories from the tests:" << endl
          << endl;
     cout << "p1: " << p1->getName() << endl;
     cout << "p2: " << p2->getName() << endl;
     cout << "t1: " << t1->getName() << " owned by " << t1->getOwner()->getName() << endl;
     cout << "t2: " << t2->getName() << " owned by " << t2->getOwner()->getName() << endl;
     cout << "t3: " << t3->getName() << " owned by " << t3->getOwner()->getName() << endl;
     cout << "t4: " << t4->getName() << " owned by " << t4->getOwner()->getName() << endl;
     cout << endl
          << endl;

     cout << "Creating Valid Advance Orders" << endl
          << endl;
     // ******************************* //
     // Creating Valid Advance orders   //
     // ******************************* //

     // p1 advance to his own territory (similar to deployment)
     Advance *a1 = new Advance(4, p1, t1, t2);
     cout << "a1: " << a1->getDetails() << endl;

     // p1 advance in enemy territory
     Advance *a1_0 = new Advance(12, p1, t2, t3);
     cout << "a1_0: " << a1_0->getDetails() << endl;

     // ********************************************************************************* //
     // Executing Valid Advance order: player source territory to player target territory   //
     // ********************************************************************************* //
     cout << endl
          << endl;
     cout << "Testing valid execution of a1: " << a1->getDetails() << endl;
     cout << "t1 before a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 before a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "********* Executing a1 ********* " << endl;
     a1->execute();
     cout << "t1 after a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 after a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     // ********************************************************************** //
     //   Executing Invalid Advance orders: insufficient source army number    //
     // ********************************************************************** //
     // This order is not valid: source territory not enough armies to advance!
     cout << endl
          << endl;
     cout << "Testing invalid execution of a1: " << a1->getDetails() << endl;
     cout << "t1 before a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 before a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "********* Executing a1 ********* " << endl;
     a1->execute();
     cout << "t1 after a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 after a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;

     // ********************************************************************************* //
     // Executing Valid Advance order: Player advance on enemy territory         //
     // ********************************************************************************* //
     /**
      * TODO: Implement simulatingAttack()
      * 
      */
     cout << endl
          << endl;
     cout << "Testing valid execution of a1_0: " << a1_0->getDetails() << endl;
     cout << "t2 before a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "t3 before a1: " << t3->getName() << ", owned by " << t3->getOwner()->getName()
          << " has " << t3->getNumberOfArmies() << " armies." << endl;
     cout << "********* Executing a1 ********* " << endl;
     a1_0->execute();
     cout << "t1 after a1_0: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "t2 after a1: " << t3->getName() << ", owned by " << t3->getOwner()->getName()
          << " has " << t3->getNumberOfArmies() << " armies." << endl;

     // ********************************************************************************* //
     // Creating Invalid Orders: Source Territory does not belong to Player                //
     // ********************************************************************************* //
     cout << endl
          << endl;
     cout << "Testing Invalid Order: Source Territory does not belong to Player" << endl;
     Advance *a2 = new Advance(5, p1, t3, t1);
     cout << "a2: " << a2->getDetails() << endl;
     a2->execute();

     /**
      * TODO: Test invalid Order when TerritoryTarget is not adjacent to TerritorySource 
      * 
      */
}

void testAirliftExec()
{
     // ************************************************** //
     //   Initialize parameters for the orders to test...
     // ************************************************** //
     Player *p1 = new Player("Hoax");
     Player *p2 = new Player("Toast");

     MapLoader *mapLoader = new MapLoader();
     Map x4 = *mapLoader->loadMap("../maps/europe.map");
     Map *map4 = new Map(x4);
     map4->validate();

     vector<Territory *> europeTerritories = map4->getTerritories();
     int numberOfTerritoryInEurope = map4->getTerritorySize();
     Territory *t1 = europeTerritories.at(0);
     Territory *t2 = europeTerritories.at(1);
     Territory *t3 = europeTerritories.at(2);
     Territory *t4 = europeTerritories.at(3);

     // To create a valid territory, need to specify owner and number of armies (if territory is conquered)
     t1->setNumberOfArmies(5);
     t1->setOwner(p1);
     t2->setNumberOfArmies(9);
     t2->setOwner(p1);
     t3->setNumberOfArmies(11);
     t3->setOwner(p2);
     t4->setNumberOfArmies(3);
     t4->setOwner(p2);

     // Player Hoax owns England, which has 5 armies
     // Player Hoax owns Scotland, which has 9 armies
     // Player Toast owns Ireland (?), which has 11 armies

     cout << "==================================="
          << endl
          << endl;

     cout << "Displaying players and territories from the tests:" << endl
          << endl;
     cout << "p1: " << p1->getName() << endl;
     cout << "p2: " << p2->getName() << endl;
     cout << "t1: " << t1->getName() << " owned by " << t1->getOwner()->getName() << ". There are " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2: " << t2->getName() << " owned by " << t2->getOwner()->getName() << ". There are " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "t3: " << t3->getName() << " owned by " << t3->getOwner()->getName() << ". There are " << t3->getNumberOfArmies() << " armies." << endl;
     cout << "t4: " << t4->getName() << " owned by " << t4->getOwner()->getName() << ". There are " << t4->getNumberOfArmies() << " armies." << endl;
     cout << endl
          << endl;

     // ******************************* //
     // Creating Valid AirLift orders   //
     // ******************************* //
     cout << "Creating Valid Advance Orders" << endl
          << endl;

     // p1 airlift correct number of armies to his own territory (valid)
     AirLift *a1 = new AirLift(4, p1, t1, t2);
     cout << "a1: " << a1->getDetails() << endl;

     // Executing a1 twice => p1 airlifts incorrect number of armies

     // p1 airlift in enemy territory (invalid)
     AirLift *a1_0 = new AirLift(12, p1, t2, t3);
     cout << "a1_0: " << a1_0->getDetails() << endl;

     cout << endl
          << endl;

     // ********************************************************************************* //
     // Executing Valid AirLift order: player source territory to player target territory   //
     // ********************************************************************************* //
     cout << endl
          << endl;
     cout << "Testing valid execution of a1: " << a1->getDetails() << endl;
     cout << "t1 before a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 before a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "********* Executing a1 (expect valid) ********* " << endl;
     a1->execute();
     cout << "t1 after a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 after a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;

     // ********************************************************************************* //
     // Executing INVALID AirLift order: Not enough armies on source territory to move   //
     // ********************************************************************************* //
     cout << endl
          << endl;
     cout << "Testing INVALID execution of a1: " << a1->getDetails() << endl;
     cout << "t1 before a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 before a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;
     cout << "********* Executing a1 (expect invalid) ********* " << endl;
     a1->execute();
     cout << "t1 after a1: " << t1->getName() << ", owned by " << t1->getOwner()->getName()
          << " has " << t1->getNumberOfArmies() << " armies." << endl;
     cout << "t2 after a1: " << t2->getName() << ", owned by " << t2->getOwner()->getName()
          << " has " << t2->getNumberOfArmies() << " armies." << endl;

     // ************************************************************** //
     // Executing invalid AirLift: Target territory owned by enemy     //
     // ************************************************************** //
     cout << endl
          << endl;
     cout << "Testing INVALID execution of a1_0: " << a1_0->getDetails() << endl;
     a1_0->execute();

     // Another test: on source territory owned by enemy
}

void testBombExec()
{
     
}


