#pragma once
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSolider.h"
#include "LinkedQueue.h"
#include "Dequeue.h"
#include "MonsterArray.h"

class AlienArmy
{
private:
	int AlienCounter;
	LinkedQueue<AlienSolider*> AS;
	Dequeue AD;
	MonsterArray AM;
public:
	AlienArmy() {
		AlienCounter = 2000;
	}
	void addUnit(unit* u);
	void print();
};

