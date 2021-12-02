#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CommandProcessor.h"
#include "GameEngine.h"

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
    else if (command == "tournament")
    {
        commandEffect = "Starting tournament mode!";
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
        commandEffect = "Game started!";
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

void Command::setArgs(vector<std::string> args) {
    this->args = args;
}

vector<std::string> Command::getArgs() {
    return args;
}

void Command::addArgs(std::string arg) {
    args.push_back(arg);
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
vector<string> CommandProcessor::readCommand(State*& currentState)
{
    vector<string> cmdInput;
    string keyIn, temp, commandName;

    cout << "Enter a valid command."
         << " (Enter x to quit)" << endl;

    getline(cin, keyIn);
    for (int i = 0; i < keyIn.length(); ++i) {
        if (keyIn[i] == ' ') {
            cmdInput.push_back(temp);
            temp = "";
        } else {
            temp.push_back(keyIn[i]);
        }
    }
    cmdInput.push_back(temp);
    commandName = cmdInput[0];

    if (commandName == "x" or this->getCurrentStateName(currentState) == "final")
        std::exit(0);
    else
    {
        cout << "\n***\n" << endl;
        return cmdInput;
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
    vector<string> command = readCommand(currentState);
    string newCommandName = command[0];
    for (int i = 1; i < command.size(); i++) {
        newCommand->addArgs(command[i]);
    }
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);

    bool isCommandValid = this->validateCommand(currentState, newCommandName);
    if (isCommandValid) {
        cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
        saveCommand(newCommand);
    } else {
        cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
    }

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
    this->fileName = newFile;
    reader = new FileLineReader();
    //reads commands from file and saves it to listOfCommands
    listOfCommands = reader->readLineFromFile(newFile);
}

//Read from file then validates. Returns whatever user input after validation
vector<string> FileCommandProcessorAdapter::readCommand(State*& currentState)
{
    vector<string> splitCommand;
    string temp, commandName;
//    if (listOfCommands.empty()) {
//        return "";
//    }
    string command = listOfCommands.at(0);
    listOfCommands.erase(listOfCommands.begin());

    for (int i = 0; i < command.length(); ++i) {
        if (command[i] == ' ') {
            splitCommand.push_back(temp);
            temp = "";
        } else {
            temp.push_back(command[i]);
        }
    }
    splitCommand.push_back(temp);
    return splitCommand;
}

Command* FileCommandProcessorAdapter::getCommand(State*& currentState)
{
    Command* newCommand = new Command();
    vector<string> command = readCommand(currentState);
    string newCommandName = command[0];
    for (int i = 1; i < command.size(); i++) {
        newCommand->addArgs(command[i]);
    }
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);

    bool isCommandValid = this->validateCommand(currentState, newCommandName);
    if (isCommandValid) {
        cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
        saveCommand(newCommand);
    } else {
        cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
    }
    return newCommand;
}

//FileLineReader used to read file commands
FileLineReader::FileLineReader()
{
}

FileLineReader::~FileLineReader()
{
}

// Handles actually reading from the file - returns each lines stacked into a string vector
std::vector<std::string> FileLineReader::readLineFromFile(string passedFile)
{
    string line;
    vector<string> listOfCommands;
    ifstream input_file(passedFile);
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