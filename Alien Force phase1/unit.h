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
	int health;
	int power;
	int attack_cap;
public:
	unit(string t, int tj, int h, int p, int ac);
	string getType();
	int getID();
	void setID(int id);
};



