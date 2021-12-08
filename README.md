# risk-game
[Warzone](https://www.warzone.com/) game on console implemented using C++. Used patterns such as `Strategy, Adapter, Observer` to implement different features.

## Setup ✨
How to Run the project:
1) Git clone the repo
2) Install tools (GCC/CMAKE & Update path variables)
3) Follow steps to under BUILD helloworld.cpp here - https://code.visualstudio.com/docs/cpp/config-clang-mac
- Create tasks.json file and update with json attributes in .vscode
- Update default build task with clang - (option should be there now that you added tasks.json)
- Go to the .cpp file you want to build and do a ``` run build task ``` under terminal -> build task
- Keep the window open and open new terminal
- Go to .cpp file you just built. Run ``` ls -la ```. See the executable. Run ./exe name 


to use cmake, in terminal go to the "build" directory of the project then execute:
    export CXX=/path/to/your/gccCompiler            --> Changes default compiler to GCC
    cmake ..                                        --> Builds the assembly
then
    make                                            --> Actually compiles the code

(path example to switch compiler for macOS)
usr/local/bin/gcc-<version>
*it's also possible to configure the compiler in vscode

    
## Team 🦄
| Name | Github Username |
|---|---|
| Alexander Abrantes Figueiras | [Figgueh](https://github.com/Figgueh) |
| Noah-James Dinh | [eyeshield2110](https://github.com/eyeshield2110) |
| Laila Chamma'a | [laila-chammaa](https://github.com/laila-chammaa) |
| Gurinder Dheer | [GD-Dheer](https://github.com/GD-Dheer) |
| Rahimuz Zaman | [ratulkai93](https://github.com/ratulkai93) |
