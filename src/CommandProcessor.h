#pragma once
#include <iostream>
#include <string>
#include <vector>

class Command;
class CommandProcessor;
class FileCommandProcessorAdapter;
class FileLineReader;
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
    void saveEffect(std::string commandEffect);
    void setCommandName(std::string name);
    std::string getCommandEffect();
};

class CommandProcessor
{
    friend class GameEngine; //To let gameengine access stuff in here
protected:
    std::vector<Command *> commands;
    virtual std::string readCommand(State*& currentState); //Get console arg
    void saveCommand(Command* c); // save Command in commands
private:
    State *currentState; 
public:
    std::string fileName;
    CommandProcessor();
    CommandProcessor(std::string fileInput, State*& setState);
    ~CommandProcessor();
    bool validateCommand(State*& currentState, std::string command);
    virtual void printCommands();
    virtual Command* getCommand(State*& currentState); // Class driver, runs everything - input is a ref to currentState pointer
    std::string getCurrentStateName(State*& currentState);
};

class FileCommandProcessorAdapter: public CommandProcessor
{
    friend class FileLineReader; 
private:
    FileLineReader* reader;
    std::string fileName;
    bool readFile;
    std::vector<std::string> listOfCommands; 
    std::string readCommand(std::string fileName, State*& currentState); // Overloaded version for adapter pattern
public:
    FileCommandProcessorAdapter(std::string newFile);
    Command* getCommand(State*& currentState);
    std::string validateCommand(State*& currentState, std::vector<std::string> &commands);
};
 
class FileLineReader 
{
    friend class FileCommandProcessorAdapter;
private:
    std::string fileName;
    std::vector<std::string> listOfCommands;
public:
    FileLineReader(std::string newFile);
    ~FileLineReader();
    std::vector<std::string> &readLineFromFile(std::string fileName);
};
