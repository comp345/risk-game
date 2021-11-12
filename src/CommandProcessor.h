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

class Command
{
private:
    std::string commandName;
    std::string commandEffect;

public:
    Command();
    Command(std::string commandName, std::string commandEffect);
    Command(const Command &c);
    ~Command();
    std::string getCommandName();
    std::string saveEffect(std::string commandEffect);
    void setCommandName(std::string name);
    std::string getEffectName();
};

class CommandProcessor
{
    friend class GameEngine;
protected:
    std::string readCommand(State* currentState); // read string from console to create Command
private:
    std::vector<Command *> commands;
    State *currentState; 
    void saveCommand(Command* c); // save Command in commands
public:
    std::string fileName;
    CommandProcessor();
    CommandProcessor(std::string fileInput);
    ~CommandProcessor();
    std::string getCurrentStateName(State* currentState);
    bool doTransition(State* currentState, std::string command);
    std::string getCommand(State* currentState); // storing string (command effect) after command is executed in GameEngine::doTransition()
    bool validateCommand(State* currentState, std::string command);
    // A2::State *currentState; 
    // std::vector<A2::State *> states; // GameEngine maintains collection of all states
    // std::vector<A2::Transition *> transitions; // GameEngine maintains collection of all valid commands/transitions
};

class FileCommandProcessorAdapter
{
private:
    std::vector<Command *> commands;
    void readCommand(Command c); // read string from file to create Command
    void saveCommand(Command c); // save Command in commands
public:
    Command *getCommand();
    void saveEffect(Command c); // storing string (command effect) after command is executed in GameEngine::doTransition()
    bool validate(Command c);
};


