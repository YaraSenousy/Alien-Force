#pragma once
#include <string.h>
#include <iostream>
#include "LinkedQueue.h"

using namespace std;

class Game;

class unit
{
private:
	int ID;
	string type;
	int Tj; //time joined
	int Td; //time dead
	int Ta; //time of first attack
protected:
	int health;
	int power;
	int attack_cap;
	Game* TheGame;
public:
	unit(string t, int tj, int h, int p, int ac, Game*& g);
	string getType();
	int getID();
	void setID(int id);
	void setHealth(int h);
	void setTimeDead(int td);
	void setTimeAttack(int ta);
	int getHealth();
	int getPower();
	int getAttack_cap();
	int getTimeJoined();
	int getTimeDead();
	int getTimeAttack();
	virtual bool attack(LinkedQueue<unit*>&,int ts) = 0;
};

inline ostream& operator<<(ostream& out, unit* u) {
	if (u) {
		out << u->getID();
	}
	return out;
}

