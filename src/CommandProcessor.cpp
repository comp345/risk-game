#include <iostream>
#include <string>
#include <vector>
#include "CommandProcessor.h"

using namespace std;



Command::Command()
{
    nameCommand = "";
}

Command::Command(string name)
{
    nameCommand = name;
}

Command::Command(const Command &c)
{
    nameCommand = c.nameCommand;
}

Command::~Command()
{
    nameCommand = "";
}


string Command::getNameCommand()
{
    return nameCommand;
}
void Command::setNameCommand(string name)
{
    nameCommand = name;
}

// read string from console to create Command
Command CommandProcessor::readCommand()
{
        string keyinput;

        cout << "Enter a valid command to progress in the game."
             << "(Enter x to quit or press any key when at final State)" << endl;

        cin >> keyinput;
        if (keyinput == "x" or engine.getCurrentStateName() == "final")
            break;
        else
        {
            cout << "\n***\n"
                 << endl;

            // Acting on the command. The function doTransition internally validates the command.
            // Returns true if command was valid, in order to display correct message.
            // TODO: switch statement to have different message for each state
            bool isCommandValid = engine.doTransition(keyinput);

            if (isCommandValid)
            {
                cout << "Valid command. Current state is: " << engine.getCurrentStateName() << endl;
            }
            else
            {
                cout << "Invalid command. Replay current state: " << engine.getCurrentStateName() << endl;
            }
        }
    //Call validate() -> Return command + effects
    return true;
} 
// save Command in commands
void CommandProcessor::saveCommand(Command c)
{
    commands.pushback(c);
} 

Command* CommandProcessor::getCommand(bool isfile=false)
{
    if(isFile)
    {
        readCommand()
    }
    Command* newCommand = new Command();
    readCommand();
    saveCommand(newCommand);
}

 // storing string (command effect) after command is executed in GameEngine::doTransition()
void Command::saveEffect(string command)
{
    if(command == 'loadmap')
    {
        effect = "Map has been loaded!"
    }
    else if(command == 'validatemap')
    {
        effect = "Map has been validated!"
    }
    else if (command == 'addplayer')
    {
        effect = "Player added! "
    }
    else if (command == 'assigncountries')
    {
        effect = "Game Engine Started!"
    }
    else if (command == 'replay')
    {
        effect = "Starting over"
    }
    else if (command == 'quit')
    {
        effect = "Exiting...!"
    }
    else
    {
        effect = "Command was shitty"
    }
}
bool Command::validate(Command c)
{
    engine.validateCommand(c.commandName);
}