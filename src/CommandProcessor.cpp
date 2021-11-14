#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "CommandProcessor.h"

using namespace std;


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
    commandName = "";
    commandEffect = "";
}

string Command::getCommandName()
{
    return commandName;
}
void Command::setCommandName(string name)
{
    commandName = name;
}

string Command::getEffectName()
{
    return commandEffect;
}

// storing string (command effect) after command is executed in GameEngine::doTransition()
string Command::saveEffect(string command)
{
    std::string effect = "";
    cout << "printing what I got in: " << command << std::endl;
    //#string mapLoaded = "maploaded";
    //#cout << "This is the variable maploaded: " << mapLoaded << std::endl;
    if(command == "maploaded")
    {
        effect = "Map has been loaded!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if(command == "mapvalidated")
    {
        effect = "Map has been validated!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "playersadded")
    {
        effect = "Player added!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "assignreinforcement")
    {
        effect = "Game Engine Started!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "start")
    {
        effect = "Starting over";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "exit")
    {
        effect = "Exiting...!";
        cout << "The effect - " << effect << std::endl; 

    }
    else
    {
        effect = "Invalid comment was entered - " + command;
        cout << "The effect - " << effect << std::endl; 
    }
    command = "";
    //cout << "The command - before exiting: " << command << std::endl;

  //  cout << "The effect - " << effect << std::endl;
    return effect;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------

CommandProcessor::CommandProcessor()
{
    fileName = "";
}

CommandProcessor::CommandProcessor(std::string fileInput, State* setState)
{
    this->fileName = fileInput;
    this->currentState = setState;
}

CommandProcessor::~CommandProcessor()
{
    this->fileName = "";
}

bool CommandProcessor::validateCommand(State* currentState, string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            cout << "Current state: " << currentState->nameState << endl;
            //*currentState->nameState;
            return true;
        }
    }
    return false;
}

std::string CommandProcessor::getCurrentStateName(State* currentState)
{
    return currentState->nameState;
}

// read string from console to create Command
std::string CommandProcessor::readCommand(State* currentState)
{
        string keyinput;

        cout << "Enter a valid command to progress in the game."
             << "(Enter x to quit or press any key when at final State)" << endl;

        cin >> keyinput;
        if (keyinput == "x" or this->getCurrentStateName(&currentState[0]) == "final")
            std::exit(0);
        else
        {
            cout << "\n***\n"
                 << endl;
            // Acting on the command. The function doTransition internally validates the command.
            // Returns true if command was valid, in order to display correct message.
            // TODO: switch statement to have different message for each state
            bool isCommandValid = this->validateCommand(&currentState[0], keyinput);

            if (isCommandValid)
            {
                cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
                return getCurrentStateName(currentState);
            }
            else
            {
                cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
                return keyinput;
            }
        
    }
   // return getCurrentStateName(currentState);
} 
// save Command in commands
void CommandProcessor::saveCommand(Command* c)
{
    commands.push_back(c);
} 

Command* CommandProcessor::getCommand(State* currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(&currentState[0]);
    cout << "get cpmmand: " << newCommandName << endl;
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommand;
}

bool CommandProcessor::doTransition(State* currentState, string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            cout << "Next state: " << *currentState->transitions.at(i)->nextState << std::endl;
            *currentState = *currentState->transitions.at(i)->nextState;
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------------------

FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string newFile)
{
    reader = new FileLineReader(newFile);
}
std::string FileCommandProcessorAdapter::readCommand(std::string fileName, State* currentState)
{
    listOfCommands = reader->readLineFromFile(fileName);
    std::string validatedCommand = this->validateCommand(&currentState[0], listOfCommands);

    if (!validatedCommand.empty())
    {
        cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
        return getCurrentStateName(currentState);
    }
    else
    {
        cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
        return validatedCommand;
    }
}

Command* FileCommandProcessorAdapter::getCommand(State* currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(fileName, currentState);
    cout << "INSIDE GET COMMAND: " << newCommandName << endl;
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommand;
}

std::string FileCommandProcessorAdapter::validateCommand(State* currentState, std::vector<std::string> &commands)
{
    //cout << "below is the command INSIDE NEW VALIDATE:: "  << "\n" << endl;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == commands[0])
        {
            cout << "Current state inside new validate: " << commands[0] << endl;
            //*currentState->nameState;
            commands.erase(commands.begin());
            return currentState->transitions.at(i)->nameTransition;
        }
    }
    return "";
}
// ------------------------------------------------------------------------------------------------------------------------

FileLineReader::FileLineReader(std::string newFile)
{
    fileName = newFile;
    //listOfCommands = null;
}

FileLineReader::~FileLineReader()
{
    //listOfCommands = 0;
}
    
// int FileLineReader::getLineNumber()
// {
//     return lineNumber;
// }

    
std::vector<std::string> FileLineReader::readLineFromFile(string passedFile) 
{
    std::vector<std::string> commands;
    int lineNumber = 0;
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
        cout << "This is each line printed: " + line + ". This is the line Number: "<< lineNumber << endl;
        commands.push_back(line);
        lineNumber++;
    }

    input_file.close();
    return commands;
}

