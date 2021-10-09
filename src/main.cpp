#include <iostream>
#include "GameEngine.h"
//using namespace GameEngineSpace;

using namespace std;

int main(int, char **)
{
    cout << "Hello, world!\n";
    // Test if orders.hpp and orders.cpp are properly linked/compiled
    testEngineLink();

    cout << "============================================\n";

    // // Test the OrderList and Order classes (and subtypes)
    // testOrdersDriver();

    return 0;
}
