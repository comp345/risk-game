#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"

#include <iostream>

using namespace std;

using namespace A2;

void testLogging()
{
    GameEngine* engine = new GameEngine();
    LogObserver* observer = new LogObserver();
    engine->attach(observer); 
    
    // transition engine to next state
    // engine->toTransition("loadmap"); // current state is "start". valid transition is "loadmap"



    OrderList* ol = new OrderList();
    Advance *advance1 = new Advance(); // parametized constrc
    ol->attach(observer);
    ol->add(advance1);

    advance1->attach(observer);
    advance1->execute();
    // save effect of order as string
    string effect = advance1->getDetails();
}

// int main()
// {
//     testLogging();
// }
