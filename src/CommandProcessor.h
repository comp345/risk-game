#pragma once
#include <iostream>
#include <string>
#include <vector>

class Command
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
};

class CommandProcessor
{
private:
    std::vector<Command *> commands;
    void readCommand(Command c); // read string from console to create Command
    void saveCommand(Command c); // save Command in commands
public:
    Command *getCommand();
    void saveEffect(Command c); // storing string (command effect) after command is executed in GameEngine::doTransition()
    bool validate(Command c);
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