#include "Player.h"
#include "orders.hpp"

int main() 
{
	OrderList* orders;
    Hand* hand;
	vector<Territory*> terr;

	Player* a1 = new Player(terr, hand, orders);
	(*a1).toAttack();
	(*a1).toDefend();
	Player* a2 = new Player(*a1);
	cout << endl;
	(*a2).toAttack();
}
