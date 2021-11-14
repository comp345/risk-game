#pragma once
#include <iostream>
#include <string>
#include <vector>


class Transition;
class State
    {
        friend class GameEngine;
        friend class Transition;
        friend class CommandProcessor;
        friend class FileCommandProcessorAdapter;

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
        friend class CommandProcessor;
        friend class FileCommandProcessorAdapter;

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