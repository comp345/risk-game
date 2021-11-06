#include <iostream>
#include <string>
#include <vector>
#include "GameEngine2.h"

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
    Transition *loadmapTransition = new Transition("loadmap", maploadedState);
    Transition *validatemapTransition = new Transition("validatemap", mapvalidatedState);
    Transition *addplayerTransition = new Transition("addplayer", playersaddedState);
    Transition *assigncountriesTransition = new Transition("assigncountries", assignreinforcementState);
    Transition *issueorderTransition = new Transition("issueorder", issueordersState);
    Transition *endissueordersTransition = new Transition("endissueorders", executeordersState);
    Transition *execorderTransition = new Transition("execorder", executeordersState);
    Transition *endexecordersTransition = new Transition("endexecorders", assignreinforcementState);
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
}

void GameEngine::doTransition(string command)
{
    // check if command (nameOfTransition) match with existing transition
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == nameOfTransition)
        {
            // Valid processing at the current state (whether new or not)
            currentState = currentState->transitions.at(i)->nextState;
            cout << "Valid command. Doing processing at current state: " << currentState->nameState << endl;
            return;
        }
    }
    // if not, display error/invalid command message!
    cout << "Invalid comand. Restart current state: " << currentState->nameState << endl;
    
}

void GameEngine::testCopyandAssignmentInGameEngine()
{
    // Test 1 : Behavior of the vector Copy Constructor when copying a vector of pointers to Transition objects.
    // "t" is the original vector, "tshallow"is the shallow copy. This is desirable.
    // When manipulating the elements of t or tshallow like this: t.at(0)->nextState = new State("End state");
    // The Transition object manipulated is the same one pointed by the element 0 (a ptr) in "t" as in "tshallow",
    // so the Transition element at 0 in both vectors will have the same new State object.

    // But when an element is removed or inserted in "t" or "tshallow", only one vector is being manipulated

    vector<Transition *> t = vector<Transition *>();
    Transition t1 = Transition("One", new State("State 1"));
    Transition t2 = Transition("Two", new State("State 2"));
    Transition t3 = Transition("Three", new State("State 3"));
    Transition t4 = Transition("Four", new State("State 4"));
    t.push_back(&t1);
    t.push_back(&t2);
    t.push_back(&t3);
    t.push_back(&t4);

    for (vector<Transition *>::iterator it = t.begin(); it != t.end(); ++it)
    {
        cout << *(*it) << endl;
    }
    cout << "___________________________________" << endl;

    // Shallow copy

    vector<Transition *> tshallow = t;
    cout << "Address of tshallow: " << &tshallow << endl; // Different from the original vector

    // Test 1 on element 0
    tshallow.erase(tshallow.begin());                                             // remove 0
    tshallow.insert(tshallow.begin(), new Transition("Un", new State("Etat 1"))); // add new element at 0; will not be the same in og
    // Test 2 on element 1
    tshallow.at(1)->nextState = new State("Etat 5"); // modifying the value of the element: will be the same in og
    // Test 3 on element 2
    tshallow.at(2) = new Transition("lambda", new State("null")); // Will only change the pointer to Transition contained in tshallow, the
    // Conclusion: copying a vector of pointer creates a new set of pointers, but towards the same Transition objects. The pointers in the vector are fundammentally different though.
    // Illustration:
    /* This is what happens
        t: 0 ---> ---> Transition object 0 <--- <--- 0 : tshallow
           1 ---> ---> Transition object 1 <--- <--- 1 : tshallow

    This is incorrect: t and tshallow do not contain the address of the same pointers to Transitions
        t: 0 ---> ---> Transition object 0
                  ^--- 0 : tshallow
        t: 1 ---> ---> Transition object 1
                  ^--- 1: tshallow
    */
    for (vector<Transition *>::iterator it2 = tshallow.begin(); it2 != tshallow.end(); ++it2)
    {
        cout << *(*it2) << endl;
    }
    cout << "___________________________________" << endl;

    cout << "Address of t: " << &t << endl;
    for (vector<Transition *>::iterator it = t.begin(); it != t.end(); ++it)
    {
        cout << *(*it) << endl;
    }

    // Test 2: Assignment operator of vector
    cout << "___________________________________" << endl;
    cout << "___________________________________" << endl;
    cout << "Testing operator=" << endl;

    vector<Transition *> copy3 = vector<Transition *>(t);
    cout << "Address of copy3: " << &copy3 << endl;
    copy3.erase(copy3.begin());
    copy3.insert(copy3.begin(), new Transition("0: copy3", new State("Stadt 33"))); // Update only in copy3, not t
    copy3.at(1) = new Transition("1: copy3", new State("Stadt 22"));                // Update only in copy3
    copy3.at(2)->nextState = new State("Stadt 55");                                 // Updates in both copy3 and t
    copy3.at(3)->nameTransition = "New name";                                       // Updates in both copy3 and t

    for (vector<Transition *>::iterator it3 = copy3.begin(); it3 != copy3.end(); ++it3)
    {
        cout << *(*it3) << endl;
    }

    cout << "___________________________________" << endl;
    cout << "Address of t: " << &t << endl;
    for (vector<Transition *>::iterator it = t.begin(); it != t.end(); ++it)
    {
        cout << *(*it) << endl;
    }

    // Deallocating
    tshallow.clear();
    t.clear();
}

void GameEngine::testGameEngine()
{
    GameEngine engine;
    // Iterating through collection of states

    cout << "Current state: " << *(engine.currentState) << endl;

    while (true)
    {
        string keyinput;
        cout << "Prompt line: Enter a valid command to traverse the graph. (Enter x to quit)" << endl;
        cin >> keyinput;
        if (keyinput == "x")
            break;
        else
        {
            cout << "______________________________________________________________________________________" << endl;
            engine.doTransition(keyinput);
        }
    }
}

int main()
{
    GameEngine::testGameEngine();

    return 0;
}
