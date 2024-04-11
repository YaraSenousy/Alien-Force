#include "unit.h"

unit::unit(string t, int tj, int h, int p, int ac)
{
	type = t;
	Tj = tj;
	health = h;
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

ostream& operator<<(ostream out, unit* u) {
	if (u) {
		out << u->getID();
	}
}