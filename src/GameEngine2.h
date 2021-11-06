#pragma once
#include <iostream>
#include <string>
#include <vector>

/* The states and transitions are stored in a linked list like structure */

// States are Nodes in the game flow
namespace A2
{
    class Transition;
    class GameEngine;
    class State
    {
        /* List of states
        - start
        - maploaded
        - mapvalidated
        - playersadded
        - assignreinforcement
        - issueorders
        - executeorders
        - win
        - final

    */

        friend class GameEngine;
        friend class Transition;

    private:
        std::string nameState;
        std::vector<Transition *> transitions;

    public:
        State();
        State(std::string name);
        State(std::string name, std::vector<Transition *> trans);
        State(const State &s);
        ~State();
        void addTransition(Transition *t);

        State &operator=(const State &o);
        friend std::ostream &operator<<(std::ostream &out, const State &s)
        {
            std::string name = s.nameState;
            out << name;
            return out;
        }
        friend std::ostream &operator<<(std::ostream &out, const Transition &trans);
    };

    // Transitions are the command that allow to change states in the game flow
    class Transition
    {
        /* List of commands and the state they point at (1-to-many)
        - invalid : repeat
        - loadmap : maploaded
        - validatemap : mapvalidated
        - addplayer : playersadded
        - assigncountries : assignreinforcement
        - issueorder : issueorders
        - endissueorders : executeorders
        - execorder : executeorders
        - endexecorders : assignreinforcement
        - win : win
        - play: start
        - end: final state
    Note: each unique transition, aside from invalid, always directs to one unique state
    Invalid transition just loops back to current state.
    */
        friend class GameEngine;
        friend class State;

    private:
        std::string nameTransition;
        State *nextState;

    public:
        Transition();
        Transition(std::string name);
        Transition(std::string name, State *s);
        Transition(const Transition &t);
        ~Transition();
        Transition &operator=(const Transition &t);
        friend std::ostream &operator<<(std::ostream &out, const Transition &trans)
        {
            std::string nextStateString;
            if (trans.nextState == NULL)
                nextStateString = "";
            else
                nextStateString = trans.nextState->nameState;

            out << "{" << trans.nameTransition << ", "
                << trans.nextState << "=" << trans.nextState->nameState << "}";
            return out;
        }
        friend std::ostream &operator<<(std::ostream &out, const State &s);
        // friend std::vector<Transition *> copyVectorOfPointers(std::vector<Transition *> vt);
    };

    class GameEngine
    {
        friend class State;
        friend class Transition;

    private:
        State *currentState;
        std::vector<State *> states;
        std::vector<Transition *> transitions;

    public:
        GameEngine();
        // ! todo: add abstraction layer, making it impossible to modify the states and transitions after instantiation
        std::string getCurrentPossibleTransitions(); // based on current state, return valid transitions
        State* getCurrentState(); 
        std::string getCurrentStateName();
        void doTransition(std::string nameOfTransition);
        static void testCopyandAssignmentInGameEngine();
        static void testGameEngine();
        friend std::ostream &operator<<(std::ostream &out, const State &s);
    };

}