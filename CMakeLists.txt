cmake_minimum_required(VERSION 3.0.0)
project(HelloWorld VERSION 0.1.0)

include(CTest)
enable_testing()

# add_executable(HelloWorld main.cpp)
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB SRC_FILES
     "src/*.cpp"
)


add_executable(HelloWorld ${SRC_FILES} src/main.cpp src/Card.cpp src/Card.h src/Map.cpp src/Map.h 
src/CardDriver.cpp src/MapDriver.cpp src/main.cpp src/Orders.cpp src/Orders.h src/OrdersDriver.cpp
src/GameEngine.cpp src/GameEngine.h src/GameEngineDriver.cpp
src/LoggingObserver.cpp src/LoggingObserver.h src/LoggingObserverDriver.cpp
src/CommandProcessor.cpp src/CommandProcessor.h src/Player.cpp src/Player.h src/PlayerDriver.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
