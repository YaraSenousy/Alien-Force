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
	void alien_attack(int as, int ad1, int ad2, int am,LinkedQueue<unit*>& as_attacked, LinkedQueue<unit*>& ad_attacked, LinkedQueue<unit*>& am_attacked, int ts);
};

