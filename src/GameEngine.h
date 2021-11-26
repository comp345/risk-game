#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "Player.h"
#include "Map.h"
#include "CommandProcessor.h"
#include "Card.h"

/* The states and transitions are stored in a linked list like structure */
class Deck;
// States are Nodes in the game flow

class State;
class Transition;
class FileCommandProcessorAdapter;
class CommandProcessor;
// class GameEngine;

class State
{
    friend class GameEngine;
    friend class Transition;
    friend class CommandProcessor;
    friend class FileCommandProcessorAdapter;

private:
    std::string nameState;
    std::vector<Transition *> transitions;

public:
    State();
    State(std::string name);
    State(std::string name, std::vector<Transition *> trans);
    State(const State &s);
    ~State();
    void addTransition(Transition *t);

    State &operator=(const State &o);
    friend std::ostream &operator<<(std::ostream &out, const State &s)
    {
        std::string name = s.nameState;
        out << name;
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, const Transition &trans);
};

// Transitions are the command that allow to change states in the game flow
class Transition
{
    friend class GameEngine;
    friend class State;
    friend class CommandProcessor;
    friend class FileCommandProcessorAdapter;

private:
    std::string nameTransition;
    State *nextState;

public:
    Transition();
    Transition(std::string name);
    Transition(std::string name, State *s);
    Transition(const Transition &t);
    ~Transition();
    Transition &operator=(const Transition &t);
    friend std::ostream &operator<<(std::ostream &out, const Transition &trans)
    {
        std::string nextStateString;
        if (trans.nextState == NULL)
            nextStateString = "";
        else
            nextStateString = trans.nextState->nameState;

        out << "{" << trans.nameTransition << ", "
            << trans.nextState << "=" << trans.nextState->nameState << "}";
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, const State &s);
};

class GameEngine : public ILoggable, public Subject
{
    friend class State;

    friend class Transition;

private:
    int numberOfPlayers;
    State *currentState;
    bool validTransition;
    bool isFile;
    std::string fileName;
    std::vector<State *> states;           // GameEngine maintains collection of all states
    std::vector<Transition *> transitions; // GameEngine maintains collection of all valid commands/transitions
    CommandProcessor *commandProcessor;
    FileCommandProcessorAdapter *fileAdapter;
    std::vector<std::string> listOfFile;
    std::vector<Player *> plVec;
    Map *map;

public:
    GameEngine();

    GameEngine(std::string fileName);

    // return name of current state
    std::string getCurrentStateName();

    // return names of possible commands in current state
    std::vector<std::string> getNextTransitions();

    // return state name if command is performed. TODO: throw exception if invalid command.
    std::string getNextStateName(std::string command);

    // check if command is valid and updates current state accordingly
    bool doTransition(std::string command);

    // check if command is valid. no update.
    bool validateCommand(std::string command);

    void testGameEngine();
    void testPart3();
    string stringToLog() override;

    /* A2 */

    // A2 Part 2
    int getNumOfPlayers();

    vector<Player *> getPlayersVect();

    void setNumOfPlayers(int plNumb);

    void getMapList();

    void randPlVec();

    void preStartup();

    Map *getMap();

    void setMap(Map *m);

    //Alexanders additions:
    void mainGameLoop();
    void reinforcementPhase(Player *p);
    void issueOrdersPhase();
    void executeOrdersPhase();
    Order *createOrderFromCard(Card *card, Player *player, Territory *territorySrc, Territory *territoryTarget);

    // Noah: Data members should be private and only accessed with public methods
    vector<Player *> currentPlayers;
    Deck *deck;
    bool allPlayersDone();
    Player *hasWinner();
    void auditPlayers();

    // Noah additions for refacting A2 part 3
    void refactoring_mainGameLoop();
};

class StartupPhase
{
private:
    GameEngine *eng;

public:
    StartupPhase();

    StartupPhase(const StartupPhase &sp);

    ~StartupPhase();

    void startup();

    void setGameEng(GameEngine *en);

    void operator=(const StartupPhase &sp);

    friend ostream &operator<<(ostream &out, const StartupPhase &sp);

    friend istream &operator>>(istream &in, const StartupPhase &sp);
};
