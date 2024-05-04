#include "EarthGunnery.h"
#include <cmath>
#include "Game.h"
bool EarthGunnery::attack(LinkedQueue<unit*>& attacked,int ts)
{
	//getting the monsters and drones lists (by reference) to attack them
	MonsterArray AM = TheGame->getAlienArmy()->getAMlist();
	Dequeue AD = TheGame->getAlienArmy()->getADlist();
	//if empty return false
	if (AD.isEmpty() && AM.isEmpty())
		return false;
	//how many monsters and AD exists
	int AM_count = AM.getCount();
	int AD_count = AD.getCount();
	 
	int AD_attack, AM_attack; //how many to attack from each
	//if there is enough of both to be attacked
	if (AM_count >= ceil(attack_cap / 2) && AD_count >= attack_cap / 2) { //if the attack capacity is odd then AM is attacked that extra one
		AM_attack = ceil(attack_cap / 2);
		AD_attack = attack_cap / 2;
	}
	//if there is not enough monsters
	else if (AM_count < ceil(attack_cap / 2)) {
		AM_attack = AM_count; //attack the rest of the monsters
		AD_attack = attack_cap - AM_attack; //attack drones with the rest of the capacity 
		if (AD_attack > AD_count) // if not enough drones, attack the rest of the drones
			AD_attack = AD_count;
	}
	//if there is not enough drones
	else if (AD_count < attack_cap / 2) {
		AD_attack = AD_count; //attack the rest of the drones
		AM_attack = attack_cap - AD_attack; //attack monsters with the rest of the capacity 
		if (AM_attack > AM_count) // if not enough monsters, attack the rest of the monsters
			AM_attack = AM_count;
	}
	Dequeue temp_AD; //store attacked AD to return to their list in correct order
	LinkedQueue<AlienMonster*> temp_AM; //store attacked AM (order doesnt matter)
	//attack the monsters
	for (int i{}; i < AM_attack; i++) {
		AlienMonster* am;
		AM.pop(am);
		int health2 = am->getHealth();
		int damage = (power * health / 100) / sqrt(health2);
		am->setHealth(health2 - damage);
		attacked.enqueue(am); //store all attacked AM to return to game
		//if the monster is killed added it to killed list
		if ((health2 - damage) <= 0) {
			am->setTimeDead(ts);
			TheGame->killed(am);
		}
		//else added it to temp list
		else
			temp_AM.enqueue(am);
	}
	//attack the drones
	for (int i{}; i < AD_attack; i++) {
		AlienDrone* ad;
		// pick once from the front and once from the back
		if (i % 2 == 0)
			AD.dequeue(ad);
		else
			AD.dequeueBack(ad);
		int health2 = ad->getHealth();
		int damage = (power * health / 100) / sqrt(health2);
		ad->setHealth(health2 - damage);
		attacked.enqueue(ad); //store all attacked AD to return to game
		//if the drone is killed added it to killed list
		if ((health2 - damage) <= 0) {
			ad->setTimeDead(ts);
			TheGame->killed(ad);
		}
		//else added it to temp list for the AD
		else if (i % 2 == 0)
			temp_AD.enqueue(ad);
		else
			temp_AD.enqueueFront(ad);

	}
	//return the alive AM to their lists 
	AlienMonster* am;
	while (temp_AM.dequeue(am)) {
		TheGame->getAlienArmy()->addUnit(am);
	}
	//return the alive AD to their lists 
	AlienDrone* ad;
	while (!temp_AD.isEmpty()) {
		if (temp_AD.dequeue(ad))
			AD.enqueue(ad);
		if (temp_AD.dequeueBack(ad))
			AD.enqueueFront(ad);
	}
	return true;
}
