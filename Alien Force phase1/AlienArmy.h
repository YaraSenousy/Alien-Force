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
	LinkedQueue<AlienSolider*> AS;
	Dequeue AD;
	MonsterArray AM;
public:
	void addUnit(unit* u);
	void print();
	LinkedQueue<AlienSolider*> &getASlist();
	Dequeue &getADlist();
	MonsterArray &getAMlist();
};

