#include "Player.h"
#include "orders.hpp"
#include <iostream>

using namespace std;

Player::Player() 
{
	vector<Territory*> territories;
	Hand* hand;
	OrderList* orderList;
}

Player::Player(vector<Territory*> t, Hand* h, OrderList* o) 
{
	this->territories = t;
	this->hand = h;
	this->orderList = o;
}

//not deep copy
Player::Player(const Player& p) 
{
	this->territories = p.territories;
	this->hand = p.hand;
	this->orderList = p.orderList;
}

Player::~Player()
{
	territories.clear();
	delete orderList;
	delete hand;
}

void Player::toAttack()
{
	for (int i = 0; i < territories.size(); i++) 
	{
		cout << territories[i] << "";
	}
	
}

void Player::toDefend() 
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout << territories[i] << "";
	}
}


void Player::issueOrder(string order) 
{
	Order o = Order(order);
	orderList->add(o);
}