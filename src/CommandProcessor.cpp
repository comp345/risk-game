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

// Getting effect of each command - returns effect string
string Command::saveEffect(string command)
{
    std::string effect = "";
    cout << "Command::saveEffect - Command Variable: " << command << std::endl;
    
    if(command == "loadmap")
    {
        effect = "Map has been loaded!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if(command == "validatemap")
    {
        effect = "Map has been validated!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "addplayer")
    {
        effect = "Player added!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "gamestart")
    {
        effect = "Game Engine Started!";
        cout << "The effect - " << effect << std::endl; 

    }
    else if (command == "replay")
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
        effect = "Invalid command was entered - " + command;
        cout << "The effect - " << effect << std::endl; 
    }
    command = "";
    return effect;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------

CommandProcessor::CommandProcessor()
{
    fileName = "";
}

CommandProcessor::CommandProcessor(std::string fileInput, State*& setState)
{
    this->fileName = fileInput;
    this->currentState = setState;
}

CommandProcessor::~CommandProcessor()
{
    this->fileName = "";
}

bool CommandProcessor::validateCommand(State*& currentState, string command)
{
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        if (currentState->transitions.at(i)->nameTransition == command)
        {
            cout << "Current state: " << currentState->nameState << endl;
            return true;
        }
    }
    return false;
}

std::string CommandProcessor::getCurrentStateName(State*& currentState)
{
    return currentState->nameState;
}

// read string from console to create Command
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
            cout << "\n***\n"
                 << endl;
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
} 

Command* CommandProcessor::getCommand(State*& currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(currentState);
    cout << "CommandProcessor::getCommand - newCommandName: " << newCommandName << endl;
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommand;
}

//------------------------------------------------------------------------------------------------------------------------

FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string newFile)
{
    //Set initial variable to has not read
    readFile = false;
    listOfCommands = {""};
    reader = new FileLineReader(newFile);
}
std::string FileCommandProcessorAdapter::readCommand(std::string fileName, State*& currentState)
{

        //cout << "Value of readFile: " << readFile << endl;
        //cout << "CHECKING SIZE OF MY VECTOR: " << listOfCommands.size() << endl;
    
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
            cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
        }
        return validatedCommand;
    
}

Command* FileCommandProcessorAdapter::getCommand(State*& currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(fileName, currentState);
    cout << "Inside FileCommandProcessorAdapter::getCommand - CommandName: " << newCommandName << endl;
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommand;
}

std::string FileCommandProcessorAdapter::validateCommand(State*& currentState, std::vector<std::string> &commands)
{
    //cout << "below is the command INSIDE NEW VALIDATE:: "  << "\n" << endl;
    for (int i = 0; i < currentState->transitions.size(); ++i)
    {
        cout << "Inside - FileCommandProcessorAdapter::validateCommand - Passed Commands : " << commands[0] << endl;
        cout << "Current size of the commands vector: " << commands.size() << std::endl;
        if(commands.size() == 0)
        {
            cout << "I hit the last element in the file: " << commands.size() << std::endl;
            return currentState->transitions.at(i)->nameTransition;
        }
        if (currentState->transitions.at(i)->nameTransition == commands[0])
        {
            cout << "Current state inside new validate: " << commands[i] << endl;
            
            //*currentState->nameState;
            commands.erase(commands.begin());
            //cout << "This is the name transition inside - validateCommandProcessor - " << currentState->transitions.at(i)->nameTransition << endl;
            return currentState->transitions.at(i)->nameTransition;
        }
    }
    commands.erase(commands.begin());
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

    
std::vector<std::string> &FileLineReader::readLineFromFile(string passedFile) 
{
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
        listOfCommands.push_back(line);
        lineNumber++;
    }
    input_file.close();
    return listOfCommands;
}

