#include <iostream>
#include <string.h>
#include <any>
#include <vector>
#include "GameEngine.h"

using namespace std;


std::vector<std::string> checkCliArgs(int argNumber,char *argv[])
{
    std::vector<std::string> args;
    for (int i = 0; i < argNumber; ++i) 
    {
        // Specifically for files
        if(argv[1] && (!strcmp(argv[i],"-f")) && argv[i+1])
        {
            args.push_back(argv[i+1]); 
        }
        
        // Hard check on arguments. 
        // Format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
        if(argv[1] && !strcmp(argv[i],"tournament") && argv[i+1] && !strcmp(argv[i+1],"-M") && argv[i+2] && argv[i+3] && !strcmp(argv[i+3],"-P") && argv[i+4] && argv[i+5] && !strcmp(argv[i+5],"-G") && argv[i+6] && argv[i+7] && !strcmp(argv[i+7],"-D") && argv[i+8])
        {
            args.push_back(argv[i+2]); // Push maps
            args.push_back(argv[i+4]); // Push player strats
            args.push_back(argv[i+6]); // Push # of games
            args.push_back(argv[i+8]); // Push # of games 
        }
    }
    return args;
}

// int main(int argc, char *argv[], char **)
// {
//     vector<std::string> args = checkCliArgs(argc, argv);

//     //args[0] contains maps
//     //args[1] contains player strats
//     //args[2] contains game number
//     //args[3] contains max turns
//     for(int i =0; i < args.size();i++)
//     {
//         cout << "This is what my array contains" << args[i] << endl;
//     }
//     if(args[0].empty())
//     {
//         GameEngine engine;
//         engine.testGameEngine();
//         //engine->preStartup(); //Replace with this eventually
//     }
//     else if(args[args.size()-1].find(".txt") != string::npos){
//         //
//         cout << "file mode" << endl;
//         GameEngine engine{args[args.size()-1]}; //Dunno how to handle yet. Can pass all to gameengine and it splits 
//                                     // Or we create 4 constructors for each case. Empty/file/tourna/tourna + file 
//         engine.testGameEngine();
//         //engine->preStartup(); //Replace with this eventually
//     }
//     else
//     {
//         GameEngine engine{args[0]};
//         engine.testGameEngine();
//         //engine->preStartup(); //Replace with this eventually
//     }
// }