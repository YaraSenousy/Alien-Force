#pragma once
#include "unit.h"
class EarthSolider : public unit
{
public:
	EarthSolider(int tj, int h, int p, int ac) : unit("ES",tj,h,p,ac){}
	void setID();
};

