#pragma once
#include "unit.h"
class AlienMonster : public unit
{
public:
	AlienMonster(int tj, int h, int p, int ac, Game* g) : unit("AM", tj, h, p, ac, g) {}
	bool attack(LinkedQueue <unit*>);
};

