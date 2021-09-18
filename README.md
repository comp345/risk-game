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

to use cmake, in terminal go to the "build" directory of the project then execute:
    export CXX=/path/to/your/gccCompiler            --> Changes default compiler to GCC
    cmake ..                                        --> Builds the assembly
then
    make                                            --> Actually compiles the code

