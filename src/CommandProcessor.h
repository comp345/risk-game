#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "States.h"

class Command;
class CommandProcessor;
class FileCommandProcessorAdapter;
class FileLineReader;

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
    virtual std::string readCommand(State*& currentState); // read string from console to create Command
    void saveCommand(Command* c); // save Command in commands
private:
    std::vector<Command *> commands;
    State *currentState; 
public:
    std::string fileName;
    CommandProcessor();
    CommandProcessor(std::string fileInput, State*& setState);
    ~CommandProcessor();
    bool validateCommand(State*& currentState, std::string command);
    virtual Command* getCommand(State*& currentState); // storing string (command effect) after command is executed
    std::string getCurrentStateName(State*& currentState);
    std::string getCurrentTransition(State*& currentState);
    bool doTransition(State*& currentState, std::string command);
   // virtual Command* getCommand(State* currentState); // storing string (command effect) after command is executed in GameEngine::doTransition()
};

class FileCommandProcessorAdapter: CommandProcessor
{
    friend class FileLineReader;
   // friend class GameEngine;
private:
    FileLineReader* reader;
    std::string fileName;
    bool readFile;
    std::vector<std::string> listOfCommands;
    std::string readCommand(std::string fileName, State*& currentState); // read string from file to create Command
public:
    FileCommandProcessorAdapter(std::string newFile);
    Command* getCommand(State*& currentState);
   // bool checkCurrentState(std::vector<std::string> commands, State* currentState);
    std::string validateCommand(State*& currentState, std::vector<std::string> &commands);

};
 
class FileLineReader 
{
    friend class FileCommandProcessorAdapter;
private:
    std::string fileName;
public:
    FileLineReader(std::string newFile);
    ~FileLineReader();
    std::vector<std::string> listOfCommands;
    std::vector<std::string> &readLineFromFile(std::string fileName);
};
