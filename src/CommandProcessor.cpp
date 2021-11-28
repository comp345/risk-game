#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CommandProcessor.h"

using namespace std;

string Command::stringToLog() {
    return "Command executed: " + this->getCommandEffect();
}

string CommandProcessor::stringToLog() {
     return "New command saved: " + commands.back()->getCommandName();
}

Command::Command()
{
    commandName = "";
    commandEffect = "";
}

Command::Command(string name, string effect)
{
    commandName = name;
    commandEffect = effect;
}

Command::Command(const Command &c)
{
    commandName = c.commandName;
    commandEffect = c.commandEffect;
}

Command::~Command()
{
}

Command& Command::operator=(const Command& c)
{
    commandName = c.commandName;
    commandEffect = c.commandEffect;
    return *this;
}

string Command::getCommandName()
{
    return commandName;
}
void Command::setCommandName(string name)
{
    commandName = name;
}

string Command::getCommandEffect()
{
    return this->commandEffect;
}

// Saving effect of each command
void Command::saveEffect(string command)
{
    if(command == "loadmap")
    {
        commandEffect = "Map has been loaded!";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else if(command == "validatemap")
    {
        commandEffect = "Map has been validated!";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else if (command == "addplayer")
    {
        commandEffect = "Player added!";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else if (command == "gamestart")
    {
        commandEffect = "Game Engine Started!";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else if (command == "replay")
    {
        commandEffect = "Starting over";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else if (command == "exit")
    {
        commandEffect = "Exiting...!";
        cout << "The effect - " << commandEffect << std::endl;

    }
    else
    {
        commandEffect = "Invalid command was entered - " + command;
        cout << "No effect - " << commandEffect << std::endl;
    }
    notify(this);
}

CommandProcessor::CommandProcessor()
{
    fileName = "";
    currentState = new State();
}
CommandProcessor::CommandProcessor(const CommandProcessor& c)
{
    fileName = c.fileName;
    currentState = new State(*c.currentState);
}

CommandProcessor::CommandProcessor(std::string fileInput, State*& setState)
{
    this->fileName = fileInput;
    this->currentState = setState;
}

CommandProcessor::~CommandProcessor()
{
}
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& c)
{
    if (this == &c)
        return *this;
    if (currentState) { delete currentState; }
    fileName = c.fileName;
    currentState = new State(*c.currentState);

    return *this;
}

bool CommandProcessor::validateCommand(State*& currentState, string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            return true;
        }
    }
    return false;
}

std::string CommandProcessor::getCurrentStateName(State*& currentState)
{
    return currentState->nameState;
}

// Reads string from console. Validates then returns input
std::string CommandProcessor::readCommand(State*& currentState)
{
    string keyinput;

    cout << "Enter a valid command to progress in the game."
         << "(Enter x to quit or press any key when at final State)" << endl;

    cin >> keyinput;
    if (keyinput == "x" or this->getCurrentStateName(currentState) == "final")
        std::exit(0);
    else
    {
        cout << "\n***\n" << endl;
        // Validates the command.
        // Returns true if command was valid, in order to display correct message.
        bool isCommandValid = this->validateCommand(currentState, keyinput);

        if (isCommandValid)
        {
            cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
        }
        else
        {
            cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
        }
        return keyinput;
    }
}

// save Command in commands vector
void CommandProcessor::saveCommand(Command* c)
{
    commands.push_back(c);
    notify(this);
}

Command* CommandProcessor::getCommand(State*& currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(currentState);
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommand;
}

// Prob going to be useful later
void CommandProcessor::printCommands()
{
    cout << "Hitting the print";
    for(Command *i : commands)
    {
        cout << "Command name: " << i->getCommandName() << endl;
        cout << "Command effect: " << i->getCommandEffect() << endl;
    }
}

//Adapter to handle reading from file. Takes a new file input and creates reader obj
FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string newFile)
{
    //Set initial variable to has not read
    readFile = false;
    listOfCommands = {""};
    reader = new FileLineReader(newFile);
}

//Read from file then validates. Returns whatever user input after validation
std::string FileCommandProcessorAdapter::readCommand(std::string fileName, State*& currentState)
{
    if(!readFile)
    {
        listOfCommands = reader->readLineFromFile(fileName);
        readFile = true;
    }

    std::string validatedCommand = this->validateCommand(currentState, listOfCommands);

    if (!validatedCommand.empty())
    {
        cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
    }
    else
    {
        cout << "Invalid command. Must check transition for current state: " << this->getCurrentStateName(currentState) << endl;
    }
return validatedCommand;
}

Command* FileCommandProcessorAdapter::getCommand(State*& currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(fileName, currentState);
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    //cout << "Inside FileCommandProcessorAdapter::getCommand - CommandName: " << newCommandName << endl; - left if needed to debug later
    return newCommand;
}

// Overloaded validate method to handle a passed vector. Returns a valid transition if true
std::string FileCommandProcessorAdapter::validateCommand(State*& currentState, std::vector<std::string> &commands)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        //cout << "Inside - FileCommandProcessorAdapter::validateCommand - Passed Commands : " << commands[0] << endl; - left if needed to debug later
        if(commands.size() == 0)
        {
            return currentState->transitions.at(i)->nameTransition;
        }
        if (currentState->transitions.at(i)->nameTransition == commands[0])
        {
            commands.erase(commands.begin());
            return currentState->transitions.at(i)->nameTransition;
        }
    }
    commands.erase(commands.begin());
    return "";
}

//FileLineReader used to read file commands
FileLineReader::FileLineReader(std::string newFile)
{
    fileName = newFile;
    listOfCommands = {};
}

FileLineReader::~FileLineReader()
{
    listOfCommands = {};
}

// Handles actually reading from the file - returns each lines stacked into a string vector
std::vector<std::string> &FileLineReader::readLineFromFile(string passedFile)
{
    string line;
    ifstream input_file(fileName);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << passedFile << "'" << endl;
        cout << "Exiting program.... Check this file again...! - " + passedFile;
        exit(0);
    }
    // Track line number while reading to check against current state
    while (getline(input_file, line))
    {
        cout << "Reading.... " + line << endl;
        listOfCommands.push_back(line);
    }
    cout << "\n";
    input_file.close();
    return listOfCommands;
}