#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameEngine2.h"
using namespace A2;

class Command
{
private:
    std::string commandName;
    std::string effect;

public:
    Command();
    Command(std::string commandName, std::string effect);
    Command(const Command &c);
    ~Command();
    std::string getCommandName();
    void saveEffect(std::string effectName);
    void setCommand(std::string name);
};

class CommandProcessor
{
    friend class GameEngine;
protected:
    Command readCommand(); // read string from console to create Command

private:
    std::vector<Command *> commands;
    GameEngine *engine;
    //Command readCommand(); // read string from console to create Command
    void saveCommand(Command c); // save Command in commands
public:
    Command *getCommand(); // storing string (command effect) after command is executed in GameEngine::doTransition()
    bool validateCommand(Command c);
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