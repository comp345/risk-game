#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"

using namespace std;

extern void refactoringA2P3();

void debuggingStateMachine(GameEngine * e);

// int main()
// {
//     // A2 Part 1
//     // GameEngine e; // solves the bug -> GameEngine * e = new GameEngine(); BUGGY
//     // e.testGameEngine();



//     // Noah refactoring a2 part 3
//     // refactoringA2P3();



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