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