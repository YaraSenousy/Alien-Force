#pragma once
#include "unit.h"
class AlienSolider : public unit
{
public:
	AlienSolider(int tj, int h, int p, int ac) : unit("AS", tj, h, p, ac) {}
};

