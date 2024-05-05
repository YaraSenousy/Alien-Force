
#include "EarthTank.h"
#include "cmath"
#include "Game.h"
bool EarthTank::attackAS = false;

bool EarthTank::attack(LinkedQueue<unit*>& attacked, int ts)
{
	// if the ES is less than 30% of AS then ET should start attacking AS for the rest of the time steps
	if (TheGame->getEarthArmy()->getESlist().getCount() < 0.3 * TheGame->getAlienArmy()->getASlist().getCount())
		attackAS = true;
	//if ES become more than or equal 80% of AS then ET should stop attacking AS for the rest of the time steps
	if (TheGame->getEarthArmy()->getESlist().getCount() > 0.8 * TheGame->getAlienArmy()->getASlist().getCount())
		attackAS = false;

	//getting the monsters and alien soldiers (by reference) to attack them
	MonsterArray AM = TheGame->getAlienArmy()->getAMlist();
	LinkedQueue<AlienSolider*> AS = TheGame->getAlienArmy()->getASlist();
	//if the lists to attack are empty return false
	if (attackAS && AM.isEmpty() && AS.isEmpty())
		return false;
	else if (!attackAS && AS.isEmpty())
		return false;

	//how many AM and AS exists
	int AM_count = AM.getCount();
	int AS_count = AS.getCount();

	int AS_attack, AM_attack; //how many to attack from each
	//if only attacking monsters
	if (!attackAS) {
		AS_attack = 0; //no AS to attack
		AM_attack = min(AM_count, attack_cap); //attack all monsters if there is not enough
	}
	else {
		//if there is enough of both to be attacked
		if (AM_count >= ceil(attack_cap / 2) && AS_count >= attack_cap / 2) { //if the attack capacity is odd then AM is attacked that extra one
			AM_attack = ceil(attack_cap / 2);
			AS_attack = attack_cap / 2;
		}
		//if there is not enough monsters
		else if (AM_count < ceil(attack_cap / 2)) {
			AM_attack = AM_count; //attack the rest of the monsters
			AS_attack = attack_cap - AM_attack; //attack drones with the rest of the capacity 
			if (AS_attack > AS_count) // if not enough drones, attack the rest of the drones
				AS_attack = AS_count;
		}
		//if there is not enough drones
		else if (AS_count < attack_cap / 2) {
			AS_attack = AS_count; //attack the rest of the drones
			AM_attack = attack_cap - AS_attack; //attack monsters with the rest of the capacity 
			if (AM_attack > AM_count) // if not enough monsters, attack the rest of the monsters
				AM_attack = AM_count;
		}
	}
	LinkedQueue<unit*> temp; //store attacked AM and AS to return to their lists (AS in correct order)
	//attack the monsters
	for (int i{}; i < AM_attack; i++) {
		AlienMonster* am;
		AM.pop(am);
		int health2 = am->getHealth();
		int damage = float(power * health / 100) / sqrt(health2);
		am->setHealth(health2 - damage);
		attacked.enqueue(am); //store all attacked AM to return to game
		//if the monster is killed added it to killed list
		if ((health2 - damage) <= 0) {
			am->setTimeDead(ts);
			TheGame->killed(am);
		}
		//else added it to temp list
		else
			temp.enqueue(am);
	}
	//attack the alien soldiers (if AS_attack isnt 0)
	for (int i{}; i < AS_attack; i++) {
		AlienSolider* as;
		AS.dequeue(as);
		int health2 = as->getHealth();
		int damage = float(power * health / 100) / sqrt(health2);
		as->setHealth(health2 - damage);
		attacked.enqueue(as); //store all attacked AS to return to game
		//if the soldier is killed added it to killed list
		if ((health2 - damage) <= 0) {
			as->setTimeDead(ts);
			TheGame->killed(as);
		}
		//else added it to temp list
		else
			temp.enqueue(as);
	}
	//return the alive AS and AM to their lists
	unit* a;
	while (temp.dequeue(a)) {
		TheGame->getAlienArmy()->addUnit(a);
	}
	return true;
}
