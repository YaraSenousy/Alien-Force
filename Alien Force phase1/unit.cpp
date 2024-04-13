#include "unit.h"

unit::unit(string t, int tj, int h, int p, int ac)
{
	type = t;
	Tj = tj;
	setHealth(h);
	power = p;
	attack_cap = ac;
}

string unit::getType()
{
    return type;
}

int unit::getID()
{
    return ID;
}

void unit::setID(int id)
{
	ID = id;
}

void unit::setHealth(int h)
{
	if (h < 0)
		health = 0;
	else if (h > 100)
		health = 100;
	else
		health = h;
}

void unit::setTimeDead(int td)
{
	Td = td;
}

int unit::getHealth()
{
	return health;
}

int unit::getPower()
{
	return power;
}

int unit::getAttack_cap()
{
	return attack_cap;
}

ostream& operator<<(ostream& out, unit* u) {
	if (u) {
		out << u->getID();
	}
	return out;
}