#pragma once
#include "unit.h"
class AlienDrone : public unit
{
public:
	AlienDrone(int tj, int h, int p, int ac) : unit("AD", tj, h, p, ac) {}
};

