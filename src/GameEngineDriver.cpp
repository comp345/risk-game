#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"

using namespace std;

void debuggingStateMachine(GameEngine * e);

// int main()
// {
//     // Debugging the state machine
//     // GameEngine * eng = new GameEngine();
//     // debuggingStateMachine(eng);
//     return 0;
// }

void debuggingStateMachine(GameEngine * e)
{
string kbInput;
    while (e->getCurrentStateName() != "final" && kbInput != "x")
    {
        e->doTransition(kbInput);
        cout << "Current state: " << e->getCurrentStateName() << endl;
        cout << "\tValid next transitions: " << endl;
        for (auto t : e->getNextTransitions())
            cout << "\t\t" << t << " -> " << e->getNextStateName(t) << endl;
        cin >> kbInput;
    }
}