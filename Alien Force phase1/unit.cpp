#include "unit.h"

unit::unit(int id, string t, int tj, int h, int p, int ac)
{
	ID = id;
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
