#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "LoggingObserver.h"

class CommandProcessor;
class FileCommandProcessorAdapter;
class FileLineReader;
class State;

class Command : public ILoggable, public Subject
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
    string stringToLog();
};

class CommandProcessor : public ILoggable, public Subject
{
    friend class GameEngine; //To let gameengine access stuff in here
protected:
    std::vector<Command *> commands;
    virtual std::string readCommand(State*& currentState); //Get console arg
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
    string stringToLog();
    void saveCommand(Command* c); // save Command in commands
};

class FileCommandProcessorAdapter: virtual public CommandProcessor
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
