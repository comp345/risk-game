#include "Map.h"
#include <iostream>
using namespace std;
int main() {
	Territory* a = new Territory("a");
	Territory* b = new Territory("b");
	Territory* c = new Territory("c");
	Territory* d = new Territory("d");
	Map map = Map();
	vector<Territory*> list = {
		b
	};
	map.addTerritory("1", a, list);
	list = {
		c
	};
	map.addTerritory("1", b, list);
	list = {
		b,d
	};
	map.addTerritory("2", c, list);
	list = {
		c,
		a
	};
	map.addTerritory("2", d, list);
	if (map.validate()) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
	delete a;
	delete b;
	delete c;
	delete d;
	a = NULL;
	b = NULL;
	c = NULL;
	d = NULL;
	return 0;
}