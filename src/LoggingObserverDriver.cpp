#include "LoggingObserver.h"
#include "GameEngine2.h"
#include "Orders.hpp"
#include <iostream>

using namespace std;


void testLogging()
{
    GameEngine* engine = new GameEngine();
    LogObserver* o = new LogObserver();
    engine->attach(o);
//    engine->run();

    OrderList* ol = new OrderList();
    Advance *advance1 = new Advance();
    ol->attach(o);
    ol->add(advance1);

    advance1->attach(o);
    advance1->execute();
}

// int main()
// {
//     testLogging();
// }
