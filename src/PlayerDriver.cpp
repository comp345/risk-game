#include "Player.h"
#include "orders.hpp"

int main()
{
    //todo: add more tests
    OrderList* orders;
    Hand* hand;
    vector<Territory*> terr;
    string name;

    Player* a1 = new Player(name, terr, hand, orders);
    a1->toAttack();
    a1->toDefend();
    Player* a2 = new Player(*a1);
    a2->toAttack();
}