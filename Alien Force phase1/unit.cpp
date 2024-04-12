#include "unit.h"

unit::unit(string t, int tj, int h, int p, int ac)
{
	type = t;
	Tj = tj;
	sethealth(h);
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

void unit::sethealth(int h)
{
	health = (h>100)? 100:h;
}

void unit::setTimeDead(int td)
{
	Td = td;
}

ostream& operator<<(ostream out, unit* u) {
	if (u) {
		out << u->getID();
	}
}