#pragma once
#include "unit.h"
class EarthGunnery : public unit
{
public:
	EarthGunnery(int tj, int h, int p, int ac, Game* g) : unit("EG", tj, h, p, ac, g) {}
};

