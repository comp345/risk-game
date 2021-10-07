#include "Player.h"
#include "orders.hpp"

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

//TODO: change to deep copy?
Player::Player(const Player& p) 
{
	this->territories = p.territories;
	this->hand = p.hand;
	this->orderList = p.orderList;
}

Player::~Player()
{
	territories.clear();
	//TODO: delete each territory pointer?
	delete[] orderList;
	orderList = NULL;
	delete[] hand;
	hand = NULL;
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