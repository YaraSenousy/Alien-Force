#pragma once
#include "unit.h"
class EarthTank : public unit
{
	static bool attackAS; //keep track if ET should be attacking AS or not
public:
	EarthTank(int tj, int h, int p, int ac, Game* g) : unit("ET", tj, h, p, ac, g) {}
	virtual bool attack(LinkedQueue<unit*>&,int);
};

