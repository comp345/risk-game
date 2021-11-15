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
    void saveEffect(std::string commandEffect);
    void setCommandName(std::string name);
    std::string getEffectName();
};

class CommandProcessor
{
    friend class GameEngine; //To let gameengine access stuff in here
protected:
    virtual std::string readCommand(State*& currentState); //Get console arg
    void saveCommand(Command* c); // save Command in commands
private:
    std::vector<Command *> commands;
    State *currentState; 
    void printCommands();
public:
    std::string fileName;
    CommandProcessor();
    CommandProcessor(std::string fileInput, State*& setState);
    ~CommandProcessor();
    bool validateCommand(State*& currentState, std::string command);
    virtual Command* getCommand(State*& currentState); // Class driver, runs everything - input is a ref to currentState pointer
    std::string getCurrentStateName(State*& currentState);
};

class FileCommandProcessorAdapter: CommandProcessor
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
