#include <iostream>
#include <vector>
// #include "Player.h"
// #include "Map.h"
#include "Orders.h"

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
        }
        else
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
Order *Order::getOrder()
{
    return this;
}
string Order::getCommand() const
{
    return command;
}
void Order::setCommand(std::string ordercommand)
{
    command = ordercommand;
}
std::string Order::getDetails() const
{
    return details;
}
void Order::setDetails(std::string orderDetails)
{
    details = orderDetails;
}

Deploy::Deploy() : Order("Deploy type", ""), armiesToMove(0),
                   playerDeploying(new Player), territoryTarget(new Territory)
{
}
// Do not use (A1 legacy)
Deploy::Deploy(string orderdetails) : Order("Deploy type", orderdetails)
{
}
/** TODO:  TO INTEGRATE IN THE ACTUAL METHOD */
Deploy::Deploy(string orderdetails, Player *p) : Deploy(orderdetails)
{
    playerDeploying->setReinforcementPool(playerDeploying->getReinforcementPool() - 1);
}
// The pointer fields Player* and Territory* are passed by reference (no deep copy)
// Note: Player* and Territory* passed as param should be ptr to dymically allocated objects
Deploy::Deploy(int armies, Player *player, Territory *territory)
{
    armiesToMove = armies;
    playerDeploying = player;
    territoryTarget = territory;
    string _command = "Deploy type";
    setCommand(_command);
    updateDetails();
    // Alexander test for game loop
    playerDeploying->setReinforcementPool(playerDeploying->getReinforcementPool() - 1);
}

/** 
 * Deploy Copy constructor 1 => can be used to create duplicate Deploy orders whose execution will be the same as the Original Deploy
 * Deep copy, with pointers of copy Deploy pointing to the same pointers (Player, Territory) as original
 * Is this desirable?
*/
// Deploy::Deploy(const Deploy &d) : Order(d.getCommand(), d.getDetails()),
// armiesToMove(d.getArmies()), playerDeploying(d.getPlayer()), territoryTarget(d.getTerritory())
// {
// }

/** Deploy Copy constructor 2 => cannot be used to create executable Deploy order with same behavior as original
 * True deep copy: Player* and Territory* of copy Deploy are not pointing to the same object as original
 */
Deploy::Deploy(const Deploy &d) : Order(d.getCommand(), d.getDetails()),
                                  armiesToMove(d.getArmies()), playerDeploying(new Player(*d.getPlayer())),
                                  territoryTarget(new Territory(*d.getTerritory()))
{
}

Deploy::~Deploy()
{
    delete playerDeploying;
    delete territoryTarget;
}

// Deep copy -> duplicate copy Deploy cannot be executed and produce the same behavior as the original Deploy
Deploy &Deploy::operator=(const Deploy &d)
{
    Order::operator=(d); // self-assign guard + assign base fields
    this->armiesToMove = d.getArmies();
    if (playerDeploying)
        delete playerDeploying;
    if (territoryTarget)
        delete territoryTarget;

    this->playerDeploying = new Player(*d.getPlayer());
    this->territoryTarget = new Territory(*d.getTerritory());
    return *this;
}
// ostream& Deploy::operator<<(std::ostream& out, const Deploy& d) {}

/**
 * Run down of creation and exec of Deploy order:
 * - Inside Part 3: issueOrdersPhase() { 
 *      determine which order to create depending on toDefend/toAttack territory, 
 *      create new <OrderSubType> (numberOfArmies, playerDeploying=engine.players[i], territoryTarget=toDefend().popFirst(), 
 *      then engine.players[i].orderList->add(o)
 *      }
 * - Inside Part 3: execOrdersPhase() { 
 *      // round robin loop: while orderList != empty for every players; for i in range(num of players))
 *      engine.players[i].orderList.at(0)->execute();
 *      // after executing the order, pop the order and finish iteration
 *      engine.players[i].orderList->remove(0);
 *      }
 */

bool Deploy::validate()
{
    cout << "Validate Deploy order." << endl;
    // cout << "this->getTerritory()->getOwner(): " << this->getTerritory()->getOwner() << endl
    // << "playerDeploying: " << playerDeploying << endl;
    if (this->getTerritory()->getOwner() != playerDeploying)
        return false;
    return true;
}
bool Deploy::execute()
{
    if (!validate()) // if invalid order
    {
        cout << "Invalid Deploy order. Exit of Deploy::execute" << endl;
        // Note about the Logger: do we notify if the order is invalid?
        return false;
    }

    cout << "Execute Deploy order." << endl;
    /** TODO: Check num of armies to deploy and Remove army units from reinforcement pool
     *      if (getPlayer()->getReinforcementPool() < getArmies()) { cout <<  << endl ;return false; }
     *      getPlayer()->setReinforcementPool(getPlayer()->getReinforcementPool() - getArmies());
     */

    // Add army units to target
    territoryTarget->setNumberOfArmies(
        getArmies() + territoryTarget->getNumberOfArmies());

    // End of exec order : orderList->remove(0);

    notify(this);
    return true;
}
int Deploy::getArmies() const { return armiesToMove; }
Player *Deploy::getPlayer() const { return playerDeploying; }
Territory *Deploy::getTerritory() const { return territoryTarget; }
void Deploy::setArmies(int armies)
{
    armiesToMove = armies;
    updateDetails();
}
void Deploy::setPlayer(Player *p)
{
    playerDeploying = p;
    updateDetails();
}
void Deploy::setTerritory(Territory *t)
{
    territoryTarget = t;
    updateDetails();
}
void Deploy::updateDetails()
{
    string _details = "Player " + playerDeploying->getName() + " deploys " + to_string(getArmies()) + " army units to " + territoryTarget->getName();
    string desc = getCommand() + " = {" + _details + "}";
    setDetails(desc);
}

string Deploy::stringToLog()
{
    return "TODO";
}

Advance::Advance() : Order("Advance type", ""), armiesToMove(0),
                     playerAdvancing(new Player), territorySource(new Territory), territoryTarget(new Territory)
{
}
// Do not use (A1 legacy)
Advance::Advance(string orderdetails) : Order("Advance type", orderdetails) // don't use
{
}
Advance::Advance(int armies, Player *player, Territory *src, Territory *target)
{
    armiesToMove = armies;
    playerAdvancing = player;
    territorySource = src;
    territoryTarget = target;
    string _command = "Advance type";
    setCommand(_command);
    updateDetails();
}
Advance::Advance(const Advance &a) : Order(a.getCommand(), a.getDetails()),
                                     armiesToMove(a.getArmies()), playerAdvancing(new Player(*a.getPlayer())),
                                     territorySource(new Territory(*a.getTerritorySource())), territoryTarget(new Territory(*a.getTerritoryTarget()))
{
}
Advance::~Advance()
{
    delete playerAdvancing;
    delete territorySource;
    delete territoryTarget;
}
Advance &Advance::operator=(const Advance &a)
{
    Order::operator=(a);
    this->armiesToMove = a.getArmies();
    if (playerAdvancing)
        delete playerAdvancing;
    if (territorySource)
        delete territorySource;
    if (territoryTarget)
        delete territoryTarget;

    this->playerAdvancing = new Player(*a.getPlayer());
    this->territorySource = new Territory(*a.getTerritorySource());
    this->territoryTarget = new Territory(*a.getTerritoryTarget());

    return *this;
}

/** TODO: Check if src and target are adjacent   */
bool Advance::validate()
{
    cout << "Debug: Validate Advance order." << endl;
    if (this->getTerritorySource()->getOwner() != playerAdvancing)
        return false;
    /** to add: check adjacency of territorytarget to territorysource, else return false
     * 
     */
    return true;
}
// Returns true if exect
bool Advance::execute()
{
    bool bonus = false; // bonus is true if advance execution leads to enemy territory conquest
    if (!validate())
    {
        cout << "Debug: Invalid Advance order." << endl;
        return false;
    }
    cout << "Debug: Execute Advance order.";

    // Case 1
    if (getTerritoryTarget()->getOwner() == playerAdvancing)
    {
        // if target belong to player, basically deploy src -> target

        /** TODO: check that num of armies ordered to advance is not greater than armies on territory source
         */
        if (getArmies() <= getTerritorySource()->getNumberOfArmies())
        {
            getTerritorySource()->setNumberOfArmies(
                getTerritorySource()->getNumberOfArmies() - getArmies());
            getTerritoryTarget()->setNumberOfArmies(
                getTerritoryTarget()->getNumberOfArmies() + getArmies());
        }
        else
        {
            cout << "Debug: Invalid number of army units to advance (greater than the number of units available on territory source." << endl;
            return false;
        }
    }
    // Case 2
    else
    {
        // if target belong to enemy...

        if (getArmies() <= getTerritorySource()->getNumberOfArmies())
        {
            // Decrease armies from source territory
            getTerritorySource()->setNumberOfArmies(
                getTerritorySource()->getNumberOfArmies() - getArmies());
            // Attack enemy
            bonus = simulateAttack();
        }
        else
        {
            cout << "Debug: Invalid number of army units to advance (greater than the number of units available on territory source." << endl;
            return false;
        }
    }
    updateDetails();
    notify(this);
    return bonus;
}
// Return true if win
// Note: simulateAttack modifies the number of armies being advanced, as they are killed
bool Advance::simulateAttack()
{
    cout << "Attacking enemy!" << endl;
    /** DONE: Implement randomized battle result
     * Attacking army and Defending alternate their attack on each other
     * Attacking army -> Defending army: each unit has 60% chance to kill
     * Defending army -> Attacking army: each unit has 70% chance to kill
     */
    int attackUnit = getArmies(), defendUnit = territoryTarget->getNumberOfArmies(); // Number of attacker and defender units alive
    int deadAttacker = 0, deadDefender = 0;                                          // body count
    bool isAttackingTurn = true;

    while (attackUnit > 0 && defendUnit > 0) // as long as player or enemy's armies are not decimated, continue battle
    {
        if (isAttackingTurn)
        {
            // cout << "Debug: Attacking army turn " << attackUnit << " ." << "rand(): " << rand() % 10 << endl;
            int resultAttack = rand() % 10;
            if (resultAttack <= 5) // Advancing player kills one defending army
            {
                territoryTarget->setNumberOfArmies(territoryTarget->getNumberOfArmies() - 1);
                cout << "Debug: Attacker kills Defender #" << to_string(++deadDefender) << endl;
                --defendUnit; // 1 defender killed
            }
        }
        else
        {
            // cout << "Debug: Defending army turn " << defendUnit << " ." << "rand(): " << rand() % 10 << endl;
            int resultAttack = rand() % 10;
            if (resultAttack <= 6) // Defending player kills one attacking army
            {
                this->setArmies(this->getArmies() - 1);
                cout << "Debug: Defender kills Attacker #" << to_string(++deadAttacker) << endl;
                --attackUnit; // 1 attacker killed
            }
        }

        isAttackingTurn = !(isAttackingTurn); // switch turn

    } // Outcome: Either all defenders are dead, or all attackers are dead
    cout << "Result of battle: "
         << "Attacker armies=" << this->getArmies()
         << " Defender armies=" << territoryTarget->getNumberOfArmies() << endl;
    // If attack wins
    bool win = (this->getArmies() > 0) ? true : false;
    if (win)
    {
        // set target armies number as remaining attacking armies
        territoryTarget->setNumberOfArmies(this->getArmies());
        // change ownership of territory
        territoryTarget->setOwner(this->getPlayer());
    }

    updateDetails(); // Advance order is modified
    return win;
}

int Advance::getArmies() const { return armiesToMove; }
Player *Advance::getPlayer() const { return playerAdvancing; }
Territory *Advance::getTerritorySource() const { return territorySource; }
Territory *Advance::getTerritoryTarget() const { return territoryTarget; }
void Advance::setArmies(int armies)
{
    armiesToMove = armies;
    updateDetails();
}
void Advance::setPlayer(Player *p)
{
    playerAdvancing = p;
    updateDetails();
}
void Advance::setTerritorySource(Territory *t)
{
    territorySource = t;
    updateDetails();
}
void Advance::setTerritoryTarget(Territory *t)
{
    territoryTarget = t;
    updateDetails();
}
void Advance::updateDetails()
{
    string _desc = getCommand() + " = {" + getPlayer()->getName() + " advances " +
                   to_string(getArmies()) + " army units from " + getTerritorySource()->getName() + " to " + getTerritoryTarget()->getName() + "}.";
    setDetails(_desc);
}

string Advance::stringToLog()
{
    return "TODO";
}

Bomb::Bomb() : Order("Bomb type", ""), playerBombing(new Player), territoryTarget(new Territory)
{
}
// DO NOT USE (A1 Legacy)
Bomb::Bomb(string orderdetails) : Order("Bomb type", orderdetails)
{
}
Bomb::Bomb(Player *player, Territory *territory)
{
    playerBombing = player;
    territoryTarget = territory;
    string _command = "Bomb type";
    setCommand(_command);
    updateDetails();
}

Bomb::Bomb(const Bomb &b) : Order(b.getCommand(), b.getDetails()), playerBombing(new Player(*b.getPlayer())),
                            territoryTarget(new Territory(*b.getTerritory()))
{
}
Bomb::~Bomb()
{
    delete playerBombing;
    delete territoryTarget;
}
Bomb &Bomb::operator=(const Bomb &b)
{
    Order::operator=(b); // self-assign guard + assign base fields
    if (playerBombing)
        delete playerBombing;
    if (territoryTarget)
        delete territoryTarget;

    this->playerBombing = new Player(*b.getPlayer());
    this->territoryTarget = new Territory(*b.getTerritory());
    return *this;
}

/** TODO: Check adjacency of target to at least one territory of player! */
bool Bomb::validate()
{
    cout << "Validate Bomb order." << endl;
    // TODO: Check adjacency
    // Check if target territory is enemy's
    if (getTerritory()->getOwner() == playerBombing)
        return false;

    return true;
}
bool Bomb::execute()
{
    if (!validate())
    {
        cout << "Invalid Bomb order." << endl;
        return false;
    }
    cout << "Execute Bomb order.";
    getTerritory()->setNumberOfArmies(
        getTerritory()->getNumberOfArmies() / 2);

    notify(this);
    return true;
}

Player *Bomb::getPlayer() const { return playerBombing; }
Territory *Bomb::getTerritory() const { return territoryTarget; }
void Bomb::setPlayer(Player *p)
{
    playerBombing = p;
    updateDetails();
}
void Bomb::setTerritory(Territory *t)
{
    territoryTarget = t;
    updateDetails();
}
void Bomb::updateDetails()
{
    string _desc = getCommand() + " = {" + getPlayer()->getName() + " bombs " +
                   getTerritory()->getName() + "}.";
    setDetails(_desc);
}

string Bomb::stringToLog()
{
    return "TODO";
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
    notify(this);
    return true;
}

string Blockade::stringToLog()
{
    return "TODO";
}

AirLift::AirLift() : Order("Airlift type", ""), armiesToMove(0),
                     playerAirlifting(new Player), territorySource(new Territory), territoryTarget(new Territory)
{
}
// DO NOT USE (A1 legacy code)
AirLift::AirLift(string orderdetails) : Order("AirLift type", orderdetails)
{
}
AirLift::AirLift(int armies, Player *player, Territory *src, Territory *target)
{
    armiesToMove = armies;
    playerAirlifting = player;
    territorySource = src;
    territoryTarget = target;
    string _command = "AirLift type";
    setCommand(_command);
    updateDetails();
}
AirLift::AirLift(const AirLift &a) : Order(a.getCommand(), a.getDetails()),
                                     armiesToMove(a.getArmies()), playerAirlifting(new Player(*a.getPlayer())),
                                     territorySource(new Territory(*a.getTerritorySource())), territoryTarget(new Territory(*a.getTerritoryTarget()))
{
}
AirLift::~AirLift()
{
    delete playerAirlifting;
    delete territorySource;
    delete territoryTarget;
}

AirLift &AirLift::operator=(const AirLift &a)
{
    Order::operator=(a);
    this->armiesToMove = a.getArmies();
    if (playerAirlifting)
        delete playerAirlifting;
    if (territorySource)
        delete territorySource;
    if (territoryTarget)
        delete territoryTarget;

    this->playerAirlifting = new Player(*a.getPlayer());
    this->territorySource = new Territory(*a.getTerritorySource());
    this->territoryTarget = new Territory(*a.getTerritoryTarget());

    return *this;
}

bool AirLift::validate()
{
    cout << "Validate AirLift order." << endl;
    if (getTerritorySource()->getOwner() != playerAirlifting ||
        getTerritoryTarget()->getOwner() != playerAirlifting)
        return false; // Only airlift from and to own territories
    return true;
}

bool AirLift::execute()
{
    cout << "Execute AirLift order.";
    if (!validate())
    {
        cout << "Debug: Invalid AirLift order." << endl;
        return false;
    }
    // Check if armiesToMove ≤ number of armies on territory source
    if (getArmies() > getTerritorySource()->getNumberOfArmies())
    {
        cout << "Debug: Invalid number of armies to AirLift" << endl;
        return false;
    }
    // Remove army units from source and AirLift army units to target
    getTerritorySource()->setNumberOfArmies(
        getTerritorySource()->getNumberOfArmies() - getArmies());
    getTerritoryTarget()->setNumberOfArmies(
        getTerritoryTarget()->getNumberOfArmies() + getArmies());

    updateDetails();
    notify(this);
    return true;
}

int AirLift::getArmies() const { return armiesToMove; }
Player *AirLift::getPlayer() const { return playerAirlifting; }
Territory *AirLift::getTerritorySource() const { return territorySource; }
Territory *AirLift::getTerritoryTarget() const { return territoryTarget; }
void AirLift::setArmies(int armies)
{
    armiesToMove = armies;
    updateDetails();
}
void AirLift::setPlayer(Player *p)
{
    playerAirlifting = p;
    updateDetails();
}
void AirLift::setTerritorySource(Territory *t)
{
    territorySource = t;
    updateDetails();
}
void AirLift::setTerritoryTarget(Territory *t)
{
    territoryTarget = t;
    updateDetails();
}
void AirLift::updateDetails()
{
    string _desc = getCommand() + " = {" + getPlayer()->getName() + " airlifts " +
                   to_string(getArmies()) + " army units from " + getTerritorySource()->getName() + " to " + getTerritoryTarget()->getName() + "}.";
    setDetails(_desc);
}

string AirLift::stringToLog()
{
    return "TODO";
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
    notify(this);
    return true;
}

//when an order is executed, output the effect of the order to the log file
string Negotiate::stringToLog()
{
    return "TODO";
}

// Implementation of OrderList
OrderList::OrderList()
{
    // list = vector<Order *>();
}
// Copy constructor of OrderList
// To Review (deep copy, see getList)
OrderList::OrderList(const OrderList &ol)
{
    list = vector<Order *>();
    list = ol.list;
}
OrderList::~OrderList()
{
    for (auto p : list)
        delete p;
    list.clear();
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

OrderList &OrderList::operator=(const OrderList &o)
{
    if (this == &o)
        return *this;
    // list.clear();
    // list = vector<Order *>();
    list = o.list;
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
    notify(this);
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

//when an order is added to the order list of a player, output the order to the log file
string OrderList::stringToLog()
{
    return "Order was added to the OrderList of a player. Order: " + this->list.back()->getCommand();
}
