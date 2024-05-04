#include "EarthSolider.h"
#include"Game.h"
bool EarthSolider::attack(LinkedQueue<unit*>& templist,int ts)
{
	//templist is the list to be returned 
	//tlist is the templist used by the function
	LinkedQueue<unit*> tlist;

	//alien solider list to attack
	LinkedQueue<AlienSolider*> AS_attacked = TheGame->getAlienArmy()->getASlist();
	
	//if alien solider list is empty, cant attack
	if (AS_attacked.isEmpty())
		return false;

	AlienSolider* as = nullptr; //alien solider being attacked
	unit* astemp = nullptr; //alien solider being attacked, different type when attacking from tlist

	//if number of alien soliders is greater than or equal to attack capacity
	//earth solider can attack with full capacity
	if (attack_cap<=AS_attacked.getCount()) {
		for (int i{}; i < attack_cap; i++) {
			AS_attacked.dequeue(as);
			int damage = (power * (health / 100)) / sqrt(as->getHealth());
			as->setHealth(as->getHealth() - damage);
			templist.enqueue(as);
			if (as->getHealth() <= 0) {
				as->setTimeDead(ts);
				TheGame->killed(as);
			}
			else
				tlist.enqueue(as);
		}
	}
	//if number of alien soliders is less than attack capacity
	//attack all alien soliders available
	else {
		//loop to attack alien soliders from list
		for (int i{}; i < AS_attacked.getCount(); i++) {
			AS_attacked.dequeue(as);
			int damage = (power * (health / 100)) / sqrt(as->getHealth());
			as->setHealth(as->getHealth() - damage);
			templist.enqueue(as);
			if (as->getHealth() <= 0) {
				as->setTimeDead(ts);
				TheGame->killed(as);
			}
			else
				tlist.enqueue(as);
		}
	}
	//return alive alien soliders to alien solider list
	//add them to templist to be returned
	while (tlist.dequeue(astemp)) {
		TheGame->getAlienArmy()->addUnit(astemp);
	}
	return true;
}
