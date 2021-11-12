#include <iostream>
#include <string>
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
        effect = "Command was shitty";
        cout << "The effect - " << effect << std::endl; 
    }
    command = "";
    cout << "The command - before exiting: " << command << std::endl;

  //  cout << "The effect - " << effect << std::endl;
    return effect;
}

CommandProcessor::CommandProcessor()
{
    fileName = "";
}

CommandProcessor::CommandProcessor(std::string fileInput)
{
    this->fileName = fileInput;
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
            cout << "Curent state: " << currentState->nameState << endl;
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
            bool isCommandValid = this->doTransition(&currentState[0], keyinput);

            if (isCommandValid)
            {
                cout << "Valid command. Current state is: " << this->getCurrentStateName(currentState) << endl;
                return getCurrentStateName(currentState);
            }
            else
            {
                cout << "Invalid command. Replay current state: " << this->getCurrentStateName(currentState) << endl;
                return "invalid";
            }
        
    }
   // return getCurrentStateName(currentState);
} 
// save Command in commands
void CommandProcessor::saveCommand(Command* c)
{
    commands.push_back(c);
} 

string CommandProcessor::getCommand(State* currentState)
{
    Command* newCommand = new Command();
    string newCommandName = readCommand(&currentState[0]);
    cout << "get cpmmand: " << newCommandName << endl;
    newCommand->setCommandName(newCommandName);
    newCommand->saveEffect(newCommandName);
    saveCommand(newCommand);
    return newCommandName;
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

State::State()
{
    nameState = "";
}
State::State(string name)
{
    nameState = name;
}
State::State(string name, vector<Transition *> t)
{
    nameState = name;
    transitions = t;
}
State::State(const State &s)
{
    nameState = s.nameState;
    transitions = vector<Transition *>(s.transitions); // Using vector copy constructor! Works, demonstration in testGameEngine
}
State::~State()
{
    transitions.clear();
}
State &State::operator=(const State &c)
{
    if (this == &c)
        return *this;
    this->nameState = c.nameState;
    this->transitions = c.transitions; // Using the vector assignment operator
    return *this;
}
void State::addTransition(Transition *t)
{
    transitions.push_back(t);
}

Transition::Transition()
{
    nameTransition = "";
    nextState = nullptr;
}
Transition::Transition(string name)
{
    nameTransition = name;
    nextState = nullptr;
}
Transition::Transition(string name, State *s)
{
    nameTransition = name;
    nextState = s;
}
Transition::Transition(const Transition &t)
{
    nameTransition = t.nameTransition;
    nextState = new State(*(t.nextState));
}
Transition::~Transition()
{
    delete nextState;
}
Transition &Transition::operator=(const Transition &t)
{
    if (this == &t)
        return *this;
    this->nameTransition = t.nameTransition;
    this->nextState = new State(*(t.nextState));
    return *this;
}