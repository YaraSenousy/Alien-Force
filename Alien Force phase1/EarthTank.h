#pragma once
#include "unit.h"
class EarthTank : public unit
{
public:
	EarthTank(int tj, int h, int p, int ac) : unit("ET", tj, h, p, ac) {}
};

