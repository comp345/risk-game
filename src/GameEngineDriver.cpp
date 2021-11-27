#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"

using namespace std;

extern void refactoringA2P3();

void debuggingStateMachine(GameEngine * e);

int main()
{
    // A2 Part 1
    GameEngine * e = new GameEngine();
    // e.testGameEngine();

    // A2 Part 3
    // e.testPart3();

    // Noah refactoring a2 part 3
    // refactoringA2P3();

    // Debuggin the state machine : the replay transition -> leads us to win state, not to start
    debuggingStateMachine(e);

    return 0;
}

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