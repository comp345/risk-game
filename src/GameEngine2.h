#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"

/* The states and transitions are stored in a linked list like structure */

// States are Nodes in the game flow
namespace A2
{
    class Transition;
    class GameEngine;
    // class Player;
    // class Map;

    class State
    {

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
    };

    class GameEngine : public ILoggable, public Subject
    {
        friend class State;
        friend class Transition;

    private:
        State *currentState;
        std::vector<State *> states;           // GameEngine maintains collection of all states
        std::vector<Transition *> transitions; // GameEngine maintains collection of all valid commands/transitions

    public:
        GameEngine();

        // return name of current state
        std::string getCurrentStateName();

        // return names of possible commands in current state
        std::vector<std::string> getNextTransitions();

        // return state name if command is performed. TODO: throw exception if invalid command.
        std::string getNextStateName(std::string command);

        // check if command is valid and updates current state accordingly
        bool doTransition(std::string command);

        // check if command is valid. no update.
        bool validateCommand(std::string command);

        static void testGameEngine();

        string stringToLog() override;

        /* A2 */

        // A2 Part 2
        void startupPhase();

        //Alexanders additions:
        void mainGameLoop();
        void reinforcementPhase(Player *p);
        void issueOrdersPhase();
        void executeOrdersPhase();

        vector<Player *> currentPlayers;
        Map *map;

        Player *hasWinner();
        void auditPlayers();
    };

}