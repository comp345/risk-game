#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "GameEngine2.h"
#include "Map.h"
#include "Player.h"
#include "Orders.h"
#include "Card.h"

using namespace std;

using namespace A2;

State::State()
{
    nameState = "";
}
State::State(string name)
{
    nameState = name;
}
State::State(string name, vector<Transition *> t)
{
    nameState = name;
    transitions = t;
}
State::State(const State &s)
{
    nameState = s.nameState;
    transitions = vector<Transition *>(s.transitions); // Using vector copy constructor! Works, demonstration in testGameEngine
}
State::~State()
{
    transitions.clear();
}
State &State::operator=(const State &c)
{
    if (this == &c)
        return *this;
    this->nameState = c.nameState;
    this->transitions = c.transitions; // Using the vector assignment operator
    return *this;
}
void State::addTransition(Transition *t)
{
    transitions.push_back(t);
}

Transition::Transition()
{
    nameTransition = "";
    nextState = nullptr;
}
Transition::Transition(string name)
{
    nameTransition = name;
    nextState = nullptr;
}
Transition::Transition(string name, State *s)
{
    nameTransition = name;
    nextState = s;
}
Transition::Transition(const Transition &t)
{
    nameTransition = t.nameTransition;
    nextState = new State(*(t.nextState));
}
Transition::~Transition()
{
    delete nextState;
}
Transition &Transition::operator=(const Transition &t)
{
    if (this == &t)
        return *this;
    this->nameTransition = t.nameTransition;
    this->nextState = new State(*(t.nextState));
    return *this;
}

// Creates the finite state machine that contains states and transitions
// The GameEngine object has access to the current state with getCurrentState(), as well
// as the valid transitions from that state with getCurrentPossibleTransitions()
GameEngine::GameEngine()
{
    // Create the states and add to states collection

    State *startState = new State("start");
    State *maploadedState = new State("maploaded");
    State *mapvalidatedState = new State("mapvalidated");
    State *playersaddedState = new State("playersadded");
    State *assignreinforcementState = new State("assignreinforcement");
    State *issueordersState = new State("issueorder");
    State *executeordersState = new State("executeorders");
    State *winState = new State("win");
    State *finalState = new State("final");

    // Adding all states in the collection of the GameEngine
    states = vector<State *>();
    states.push_back(startState);
    states.push_back(maploadedState);
    states.push_back(mapvalidatedState);
    states.push_back(playersaddedState);
    states.push_back(assignreinforcementState);
    states.push_back(issueordersState);
    states.push_back(executeordersState);
    states.push_back(winState);
    states.push_back(finalState);

    // Setting current state to the start state
    currentState = startState;

    // Create the transitions
    Transition *loadmapTransition = new Transition("1", maploadedState);
    Transition *validatemapTransition = new Transition("2", mapvalidatedState);
    Transition *addplayerTransition = new Transition("3", playersaddedState);
    Transition *assigncountriesTransition = new Transition("4", assignreinforcementState);
    Transition *issueorderTransition = new Transition("5", issueordersState);
    Transition *endissueordersTransition = new Transition("6", executeordersState);
    Transition *execorderTransition = new Transition("7", executeordersState);
    Transition *endexecordersTransition = new Transition("8", assignreinforcementState);
    Transition *winTransition = new Transition("win", winState);
    Transition *playTransition = new Transition("play", startState);
    Transition *endTransition = new Transition("end", finalState);

    // Add transition to collection of transitions
    transitions = vector<Transition *>();
    transitions.push_back(loadmapTransition);
    transitions.push_back(validatemapTransition);
    transitions.push_back(addplayerTransition);
    transitions.push_back(assigncountriesTransition);
    transitions.push_back(issueorderTransition);
    transitions.push_back(endissueordersTransition);
    transitions.push_back(execorderTransition);
    transitions.push_back(endexecordersTransition);
    transitions.push_back(winTransition);
    transitions.push_back(playTransition);
    transitions.push_back(endTransition);

    // Add transitions to the states
    startState->addTransition(loadmapTransition);
    maploadedState->addTransition(loadmapTransition);
    maploadedState->addTransition(validatemapTransition);
    mapvalidatedState->addTransition(addplayerTransition);
    playersaddedState->addTransition(addplayerTransition);
    playersaddedState->addTransition(assigncountriesTransition);
    assignreinforcementState->addTransition(issueorderTransition);
    issueordersState->addTransition(issueorderTransition);
    issueordersState->addTransition(endissueordersTransition);
    executeordersState->addTransition(execorderTransition);
    executeordersState->addTransition(endexecordersTransition);
    executeordersState->addTransition(winTransition);
    winState->addTransition(playTransition);
    winState->addTransition(endTransition);

    //Initialization
    currentPlayers = vector<Player *>();
    deck = new Deck(30);
}

string GameEngine::getCurrentStateName()
{
    return currentState->nameState;
}

vector<string> GameEngine::getNextTransitions()
{
    vector<string> transitionsNames;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        transitionsNames.push_back(currentState->transitions.at(i)->nameTransition);
    }
    return transitionsNames;
}

string GameEngine::getNextStateName(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            return currentState->transitions.at(i)->nextState->nameState;
        }
    }
    return ""; //TODO: throw exception
}

// Only check if command is valid. Does NOT act upon the command, even if it is valid.
bool GameEngine::validateCommand(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            return true;
        }
    }
    return false;
}

// Check if command is valid. If it is, updates the state. Return true if command was valid, false if else.
// The success and error messages are not implemented, to allow flexible implementation in differents parts of A2.
bool GameEngine::doTransition(string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            currentState = currentState->transitions.at(i)->nextState;
            return true;
        }
    }
    return false;
}

// Game play implementation for A1.
// TODO: Will need to divide game flow into StartUpPhase(), GameLoopPhase(), etc. for A2
void GameEngine::testGameEngine()
{

    GameEngine engine;
    cout << "Welcome to WarZone!" << endl;
    cout << "Current State: " << engine.getCurrentStateName() << endl;
    cout << "Printing deck: " << endl;
    engine.deck->showDeck();

    while (true)
    {
        string keyinput;

        cout << "\nEnter a valid command to progress in the game."
             << "(Enter x to quit or press any key when at final State)" << endl;

        cin >> keyinput;
        if (keyinput == "x" or engine.getCurrentStateName() == "final")
            break;
        else
        {
            cout << "\n***\n"
                 << endl;

            // Acting on the command. The function doTransition internally validates the command.
            // Returns true if command was valid, in order to display correct message.
            // TODO: switch statement to have different message for each state
            bool isCommandValid = engine.doTransition(keyinput);

            if (isCommandValid)
            {
                cout << "Valid command. Current state is: " << engine.getCurrentStateName() << endl;
            }
            else
            {

                cout << "Invalid command. Replay current state: " << engine.getCurrentStateName() << endl;
            }

            // Noah comment on part 3: why
            // engine.currentState = new State("mapvalidated");

            if (engine.currentState->nameState == "mapvalidated")
            {
                MapLoader *mapLoader = new MapLoader();
                Map x5 = *mapLoader->loadMap("../maps/france.map");
                Map *map5 = new Map(x5);
                map5->validate();
                engine.map = map5;
            }

            else if (engine.currentState->nameState == "playersadded")
            {
                Player *p = new Player("Alexander");
                p->setReinforcementPool(0);

                //Get the latest continent from the maps
                Continent *mapsContinent = engine.map->continentList.at(0);
                vector<Territory *> p1Territories;
                for (Territory *t : mapsContinent->territories)
                {
                    p1Territories.push_back(t);
                }
                p->setTerritories(p1Territories);

                //Show what we created
                cout << "\n\n"
                     << p->getName() << " was created!\n";
                for (Territory *t : p->getTerritories())
                {
                    cout << t->getName() << "\n";
                    t->setNumberOfArmies(2);
                    t->setOwner(p);
                }
                p->getTerritories().front()->setNumberOfArmies(4); //Offset to see if soarting is working.
                engine.currentPlayers.push_back(p);
                cout << "For this continent there are " << mapsContinent->numOfTerritories << " number of territories and " << mapsContinent->controlBonus << " Control bonus.";

                //Do the same for another player
                Player *p2 = new Player("Andrew");
                p2->setReinforcementPool(0);

                mapsContinent = engine.map->continentList.at(1);
                vector<Territory *> p2Territories;
                for (Territory *t : mapsContinent->territories)
                {
                    p2Territories.push_back(t);
                }
                p2->setTerritories(p2Territories);

                cout << "\n\n"
                     << p2->getName() << " was created! \n";
                for (Territory *t : p2->getTerritories())
                {
                    cout << t->getName() << "\n";
                    t->setNumberOfArmies(5);
                    t->setOwner(p2);
                }
                engine.currentPlayers.push_back(p2);
                cout << "For this continent there are " << mapsContinent->numOfTerritories << " number of territories and " << mapsContinent->controlBonus << " Control bonus.";

                //Empty player
                Player *p3 = new Player("noob");
                p3->setReinforcementPool(0);
                vector<Territory *> p3Territories = vector<Territory *>();
                p3->setTerritories(p3Territories);
                cout << "\nNumber of territories: " << p3->getTerritories().size() << "\n";
                engine.currentPlayers.push_back(p3);

                //Add a unit in a neighbouring territory to see if priortiy works
                // for(Territory* t : engine.map->getTerritories())
                // {
                //     if(t->getName() == "Cher"){
                //         t->setNumberOfArmies(10);
                //         t->setOwner(p3);    //P3 is the noob player, he isnt supposed to have territories
                //     }
                // }

                // Player* winner = new Player("Pro");
                // vector<Territory*> allTerritories = engine.map->getTerritories();
                // winner->setTerritories(allTerritories);
                // engine.currentPlayers.push_back(winner);
            }
        }
        // Noah debug line A2
        cout << "Debug: Entering mainGameLoop" << endl;
        engine.mainGameLoop();
    }
}

string GameEngine::stringToLog()
{
    return "TODO";
}

void GameEngine::mainGameLoop()
{
    if (getCurrentStateName() == "assignreinforcement")
    {
        for (Player *p : currentPlayers)
        {
            reinforcementPhase(p);
            cout << "\nPlayer: " << p->getName() << " has " << p->getReinforcementPool() << " in his reinforcement pool.\n";
        }
    }

    if (currentState->nameState == "issueorder")
    {
        // Testing cards (Noah and Laila)
        // Create 5 dummy cards for each player
        deck->draw(*currentPlayers.at(0));
        deck->draw(*currentPlayers.at(0));
        deck->draw(*currentPlayers.at(0));
        deck->draw(*currentPlayers.at(0));
        deck->draw(*currentPlayers.at(0));
        deck->draw(*currentPlayers.at(1));
        deck->draw(*currentPlayers.at(1));
        deck->draw(*currentPlayers.at(1));
        deck->draw(*currentPlayers.at(1));
        deck->draw(*currentPlayers.at(1));

        //dummy order
        // Deploy *deployOrder = new Deploy("random order");
        // currentPlayers.at(0)->getOrderList()->add(deployOrder);
        // currentPlayers.at(0)->getOrderList()->add(deployOrder);
        // currentPlayers.at(1)->getOrderList()->add(deployOrder);
        // currentPlayers.at(1)->getOrderList()->add(deployOrder);

        Territory *currentPlayerTerritory = currentPlayers.front()->getTerritories().front();
        Advance *advanceOrder = new Advance(1, currentPlayers.front(), currentPlayers.front()->getTerritories().front(), currentPlayers.front()->getTerritories().back());
        currentPlayers.front()->getOrderList()->add(advanceOrder);

        issueOrdersPhase();
    }

    if (currentState->nameState == "executeorders")
    {
        executeOrdersPhase();
    }

    // loop shall continue until only one of the players owns all the territories
    Player *winner = hasWinner();
    if (winner != NULL)
    {
        currentState = new State("win");
        cout << "\nPlayer " << winner->getName() << " won the game!\n";
    }

    // loop to check if a player should be removed from the game
    auditPlayers();
}

void GameEngine::auditPlayers()
{
    for (Player *p : currentPlayers)
    {
        if (p->getTerritories().size() == 0)
        {
            cout << "\nPlayer " << p->getName() << " no longer has any territories left and will be removed from the game \n";

            currentPlayers.erase(remove(currentPlayers.begin(), currentPlayers.end(), p));

            delete p;
            p = NULL;
        }
    }
}

Player *GameEngine::hasWinner()
{
    //Get the players territories
    for (Player *p : currentPlayers)
    {

        if (map->getTerritories().size() == p->getTerritories().size())
        {
            return p;
        }
    }

    return NULL;
}

void GameEngine::reinforcementPhase(Player *p)
{
    // Check if player won territories in the last round. If yes, draw one card for each
    // -> Player class needs prevTerritoriesSize() and currentTerritoriesSize()
    int numConqueredTerritories = p->getTerritorySize() - p->getPrevTerritorySize();
    for (int i = 0; i < numConqueredTerritories; ++i)
    {
        deck->draw(*p);
    }
    // update prevTerritorySize
    p->setPrevTerritorySize();

    //Get players number of territories

    int numberOfArmies = floor(p->getTerritorySize() / 3);

    //Find if the player owns all the territories of an entire contenent:
    int controlBonus = 0;
    bool ownsContinent = false;

    //Get all the continents then their territories:
    for (Continent *c : map->continentList)
    {
        int territoryCount = 0;
        controlBonus = c->controlBonus;
        vector<Territory *> listOfContentsTerritories = c->territories;

        //Loop through what the player has to check if the owns the full continent
        for (Territory *t : p->getTerritories())
        {

            //Count of how many of the players Territories we find of the continent
            if (find(listOfContentsTerritories.begin(), listOfContentsTerritories.end(), t) != listOfContentsTerritories.end())
            {
                territoryCount++;
            }
        }

        //If both are equal sizes, then players owns continent.
        if (territoryCount == listOfContentsTerritories.size())
            ownsContinent = true;

        if (ownsContinent == true)
        {
            cout << "continent bonus has been applied! adding an additional " << controlBonus << " units";
            numberOfArmies += controlBonus;
            ownsContinent = false;
        }
    }

    //the minimal number of reinforcement armies per turn for any player is 3
    if (numberOfArmies < 3)
        numberOfArmies = 3;

    // placed in the player’s reinforcement pool.
    p->setReinforcementPool(p->getReinforcementPool() + numberOfArmies);
}

// returns false if someone is still issuing orders
bool GameEngine::allPlayersDone()
{
    for (Player *p : currentPlayers)
    {
        if (!p->isDoneIssuing())
            return false;
    }

    return true;
}

void GameEngine::issueOrdersPhase()
{
    // Updating each players' toAttack and toDefend queues
    for (Player *p : currentPlayers)
    {
        // territories are to be attacked in priority
        for (Territory *toAttack : p->toAttack())
        {
            p->addToPriorityAttack(toAttack);
        }
        // Defend
        for (Territory *toDefend : p->toDefend())
        {
            p->addToPriorityDefend(toDefend);
        }
    }
    // Round Robin
    // no reinforcement
    // empty
    while (!allPlayersDone())
    {
        for (int i = 0; i < currentPlayers.size(); i++)
        {
            cout << "\nGameEngine:: Player: " << currentPlayers.at(i)->getName() << " is currently in the issue order phase.\n";

            if (currentPlayers.at(i)->isDoneIssuing())
                continue;

            // (1) Deploy: until reinforc pool == 0
            if (currentPlayers.at(i)->getReinforcementPool() > 0)
            {
                Territory *territoryTarget = currentPlayers.at(i)->getPriorityDefending().top();
                // Create Deploy -> decrease reinforcement)
                Deploy *deploy = new Deploy(1, currentPlayers.at(i), territoryTarget);
                cout << "Issueing: " << deploy->getDetails() << endl;
                currentPlayers.at(i)->issueOrder(deploy);
                /* To do for A3: Able to use same territory in deploy order for advance (add stack to store popped defending territory?) */
                currentPlayers.at(i)->popPriorityDefend();
            }
            else if (currentPlayers.at(i)->getPriorityDefending().size() > 0 and currentPlayers.at(i)->getPriorityAttacking().size() > 0)
            {
                // (3) Advance
                Player *currentPlayer = currentPlayers.at(i);
                Territory *territorySource = currentPlayer->getPriorityDefending().top();
                Territory *territoryTarget = currentPlayer->getPriorityAttacking().top(); // problem is empties before priorityDefending
                Advance *advance = new Advance(1, currentPlayer, territorySource, territoryTarget);
                cout << "Issueing! " << advance->getDetails() << endl;
                currentPlayer->issueOrder(advance);
                currentPlayer->popPriorityAttack();
                currentPlayer->popPriorityDefend();
            }
            else
            {
                // For A3? Add ability to play cards altho we can see create advance orders
                // (2) Card
                Player *currentPlayer = currentPlayers.at(i);


            }

            // After a player issue one order, check if reinforcementPool 0 or queues empty
            if (currentPlayers.at(i)->getPriorityDefending().size() == 0 or currentPlayers.at(i)->getPriorityAttacking().size() == 0)
                currentPlayers.at(i)->toggleDoneIssuing();
        }
    }
}

Order *GameEngine::createOrderFromCard(Card *card)
{
    return NULL;
}

bool hasOrders(vector<Player *> currentPlayers)
{
    for (Player *player : currentPlayers)
    {
        if (player->getOrderList()->getList().size() != 0)
            return false;
    }
    return true;
}

void GameEngine::executeOrdersPhase()
{
    //players have signified that they are not issuing one more order
    bool hasDeploy = false;

    while (!hasOrders(currentPlayers))
    {
        //Iterate over each player
        for (int i = 0; i < currentPlayers.size(); i++)
        {
            Player *currentPlayer = currentPlayers.at(i);
            bool played = false;

            cout << "GameEngine:: Player: " << currentPlayer->getName() << " is currently in the execute order phase.\n";
            //Check to see if that player has a deploy order
            for (Order *order : currentPlayer->getOrderList()->getList())
            {
                // cout << order->getCommand() << "\n";
                if (order->getCommand() == "Deploy type")
                {
                    hasDeploy = true;
                    break;
                }
            }

            if (hasDeploy = true)
            {
                //Go through all the order
                for (Order *order : currentPlayers.at(i)->getOrderList()->getList())
                {
                    //Play the deploy order first
                    if (order->getCommand() == "Deploy type")
                    {
                        cout << "GameEngine:: Player: " << currentPlayer->getName() << " is issuing a deploy order.\n";
                        order->execute();
                        played = true;
                        break;
                    }
                }

                // continue to let other players deploy their armies after 1 occurrence
                // if(played == true)
                //     continue;
            }

            else
            {
                //Go through all the order
                for (Order *order : currentPlayers.at(i)->getOrderList()->getList())
                {
                    //Play the other orders
                    cout << "GameEngine:: Player: " << currentPlayer->getName() << " is issuing a " << order->getCommand() << " order.\n";
                    order->execute();
                    played = true;
                    break;
                }
                // continue to let other players execute orders before continuing.
                // if(played == true)
                //     continue;
            }

            //Remove it from the list of orders
            if (currentPlayers.at(i)->getOrderList()->getList().size() != 0)
                currentPlayers.at(i)->getOrderList()->remove(0);
        }
    }

    // for(Player* players : currentPlayers)
    // {
    //     for(Order* order : players->getOrderList()->getList())
    //     {
    //         order->execute();
    //     }
    // }

    //the main game loop goes back to the reinforcement phase
    currentState = new State("assignreinforcement");
}
