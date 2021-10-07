# risk-game
On Windows:
Video for path variables:
https://www.youtube.com/watch?v=VtEstN5gOts
I dont recommend installing it where he does, but the idea is the same for everything else


If building isn't working:
https://github.com/microsoft/vscode-cmake-tools/issues/880#issuecomment-598996051

You'll have to make sure that you have the correct paths to where your cmake and gcc are!!


On mac:
Download gcc from homebrew, also cmake from the website


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