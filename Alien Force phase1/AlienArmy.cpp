#include "AlienArmy.h"
#include "unit.h"

void AlienArmy::addUnit(unit* u) {
	u->setID(AlienCounter);
	AlienCounter++;

	if (u->getType() == "AS") {
		AS.enqueue(static_cast<AlienSolider*> (u));
	}
	else if (u->getType() == "AM") {
		AM.push(static_cast<AlienMonster*>(u));
	}
	else if (u->getType() == "AD") {
		AlienDrone* drone = static_cast<AlienDrone*> (u);
		AD.enqueue(drone);
	}
}

void AlienArmy::print()
{
	cout << "============== Alien Army Alive Units =================" << endl;
	cout << AS.getCount() << " AS ";
	AS.print();
	cout << endl << AM.getCount() << " AM ";
	AM.print();
	cout << endl << AD.getCount() << " AD ";
	AD.print();
	cout << endl;
}

LinkedQueue<AlienSolider*> AlienArmy::getASlist()
{
	return AS;
}

Dequeue AlienArmy::getADlist()
{
	return AD;
}

MonsterArray AlienArmy::getAMlist()
{
	return AM;
}
