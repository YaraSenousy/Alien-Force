#include "AlienArmy.h"
#include "unit.h"

void AlienArmy::addUnit(unit* u) {

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

LinkedQueue<AlienSolider*> &AlienArmy::getASlist()
{
	return AS;
}

Dequeue &AlienArmy::getADlist()
{
	return AD;
}

MonsterArray &AlienArmy::getAMlist()
{
	return AM;
}

void AlienArmy::alien_attack(LinkedQueue<unit*>& as, LinkedQueue<unit*>& ad, LinkedQueue<unit*>& am, int ts)
{
	AlienSolider* as_attack;
	//pick a soldier to attack
	if (AS.peek(as_attack)) {
		as_attack->attack(as, ts);
		//if it is the first time to attack set Ta with time stamp
		if (as_attack->getTimeAttack() == -1)
			as_attack->setTimeAttack(ts);
	}
	AlienDrone* ed1_attack;
	AlienDrone*	ed2_attack;
	//pick two drone from the front and back to attack
	if (AD.peek(ed1_attack) && AD.peekBack(ed2_attack)) {
		ed1_attack->attack(ad, ts);
		ed2_attack->attack(ad, ts);
		//if it is the first time to attack set Ta with time stamp
		if (ed1_attack->getTimeAttack() == -1)
			ed1_attack->setTimeAttack(ts);
		if (ed2_attack->getTimeAttack() == -1)
			ed2_attack->setTimeAttack(ts);
	}
	AlienMonster* am_attack;
	//pick a monster to attack
	if (AM.peek(am_attack)) {
		am_attack->attack(am, ts);
		//if it is the first time to attack set Ta with time stamp
		if (am_attack->getTimeAttack() == -1)
			am_attack->setTimeAttack(ts);
	}
}
