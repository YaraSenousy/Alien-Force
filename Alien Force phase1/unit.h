#pragma once
#include <string.h>
#include <iostream>

using namespace std;

class unit
{
private:
	int ID;
	string type;
	int Tj;
	int Td;
	int health;
	int power;
	int attack_cap;
public:
	unit(string t, int tj, int h, int p, int ac);
	string getType();
	int getID();
	void setID(int id);
	void setHealth(int h);
	void setTimeDead(int td);
	int getHealth();
	int getPower();
	int getAttack_cap();
};

inline ostream& operator<<(ostream& out, unit* u) {
	if (u) {
		out << u->getID();
	}
	return out;
}

