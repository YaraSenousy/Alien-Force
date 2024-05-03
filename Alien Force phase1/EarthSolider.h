#pragma once
#include "unit.h"
class EarthSolider : protected unit
{
public:
	EarthSolider(int tj, int h, int p, int ac, Game* g) : unit("ES", tj, h, p, ac, g) {};
	virtual LinkedQueue <unit*> attack();
};

