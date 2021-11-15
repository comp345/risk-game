#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"

class Command : public ILoggable, public Subject
{
private:
    std::string nameCommand;

public:
    Command();
    Command(std::string name);
    Command(const Command &c);
    ~Command();
    std::string getNameCommand();
    void setNameCommand(std::string name);
    void saveEffect();
    string stringToLog();
};

class CommandProcessor : public ILoggable, public Subject
{
private:
    std::vector<Command *> commands;
    void readCommand(Command c); // read string from console to create Command
    void saveCommand(Command c); // save Command in commands
public:
    Command *getCommand();
    bool validate(Command c);
    string stringToLog();
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