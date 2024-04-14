#pragma once
#include "EarthSolider.h"
#include "EarthTank.h"
#include "EarthGunnery.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "ArrayStack.h"

class EarthArmy
{
private:
	int EarthCounter;
	LinkedQueue<EarthSolider*> ES;
	ArrayStack<EarthTank*> ET;
	priQueue<EarthGunnery*> EG;
public:
	EarthArmy() {
		EarthCounter = 1;
	}
	void addUnit(unit* u);
	void print();
	LinkedQueue<EarthSolider*>& getESlist();
	ArrayStack<EarthTank*>& getETlist();
	priQueue<EarthGunnery*>& getEGlist();
};

