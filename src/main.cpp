#include <iostream>
#include "orders.hpp"

using namespace std;

int main(int, char **)
{
    cout << "Hello, world!\n";
    // Test if orders.hpp and orders.cpp are properly linked/compiled
    testOrdersLink();

    cout << "============================================\n";

    // Test the OrderList and Order classes (and subtypes)
    testOrdersDriver();

    return 0;
}
