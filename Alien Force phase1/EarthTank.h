#pragma once
#include "unit.h"
class EarthTank : public unit
{
public:
	EarthTank(int tj, int h, int p, int ac, Game* g) : unit("ET", tj, h, p, ac, g) {}
};

