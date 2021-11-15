#include <iostream>
#include <string>
#include <vector>
#include "CommandProcessor.h"

using namespace std;

string Command::stringToLog() {
    return "Command executed: " + nameCommand;
}

string CommandProcessor::stringToLog() {
    // return "New command saved: " + commands.back()->getNameCommand();
    return "New command saved: TODO";
}