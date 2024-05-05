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

void AlienArmy::alien_attack(int& as, int& ad1,int& ad2, int& am, LinkedQueue<unit*>& as_attacked, LinkedQueue<unit*>& ad_attacked, LinkedQueue<unit*>& am_attacked, int ts)
{
	//initialise the ids of the army units that are going to attack
	as = 0;
	ad1 = 0;
	ad2 = 0;
	am = 0;
	AlienSolider* as_attack;
	//pick a soldier to attack
	if (AS.peek(as_attack)) {
		if (as_attack->attack(as_attacked, ts)) { //if the alien found soldiers to attack
			as = as_attack->getID(); //send the id of attacking AS to game
			//if it is the first time to attack set Ta with time stamp
			if (as_attack->getTimeAttack() == -1)
				as_attack->setTimeAttack(ts);
		}
	}
	AlienDrone* ad1_attack;
	AlienDrone*	ad2_attack;
	//pick two drone from the front and back to attack
	if (AD.peek(ad1_attack) && AD.peekBack(ad2_attack)) {
		if (ad1_attack->attack(ad_attacked, ts)) { //if the first drone found earth units to attack, then we consider that both of them attacked (even if the second didnt find)
			ad2_attack->attack(ad_attacked, ts); // second drone attacks

			ad1 = ad1_attack->getID(); //send the id of attacking AD to game
			//if it is the first time to attack set Ta with time stamp
			if (ad1_attack->getTimeAttack() == -1)
				ad1_attack->setTimeAttack(ts);

			ad2 = ad2_attack->getID();
			if (ad2_attack->getTimeAttack() == -1)
				ad2_attack->setTimeAttack(ts);
		}
	}
	AlienMonster* am_attack;
	//pick a monster to attack
	if (AM.peek(am_attack)) {
		if (am_attack->attack(am_attacked, ts)) { //if the monster found earth units to attack
			am = am_attack->getID(); //send the id of attacking AM to game
			//if it is the first time to attack set Ta with time stamp
			if (am_attack->getTimeAttack() == -1)
				am_attack->setTimeAttack(ts);
		}
	}
}

