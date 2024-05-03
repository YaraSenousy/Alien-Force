#include "unit.h"

unit::unit(string t, int tj, int h, int p, int ac, Game* g)
{
	type = t;
	Tj = tj;
	setHealth(h);
	power = p;
	attack_cap = ac;
	TheGame = g;
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

void unit::setTimeAttack(int ta)
{
	Ta = ta;
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

int unit::getTimeJoined()
{
	return Tj;
}

int unit::getTimeDead()
{
	return Td;
}

int unit::getTimeAttack()
{
	return Ta;
}

