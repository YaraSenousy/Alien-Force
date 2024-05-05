#include "AlienSolider.h"
#include "Game.h"
bool AlienSolider::attack(LinkedQueue<unit*> &templist,int ts)
{
	//templist is the list to be returned 
	//tlist is the templist used by the function
	LinkedQueue<unit*> tlist;

	//earth solider list to attack
	LinkedQueue<EarthSolider*>& ES_attacked = TheGame->getEarthArmy()->getESlist();

	//if earth solider list is empty, cant attack
	if (ES_attacked.isEmpty())
		return false;

	EarthSolider* es = nullptr; //earth solider being attacked
	unit* estemp = nullptr; //earth solider being attacked, different type to dequeue from tlist

	//if number of earth soliders is greater than or equal to attack capacity
	//alien solider can attack with full capacity
	if (attack_cap <= ES_attacked.getCount()) {
		for (int i{}; i < attack_cap; i++) {
			ES_attacked.dequeue(es);
			int damage = (power * health / 100) / sqrt(es->getHealth());
			es->setHealth(es->getHealth() - damage);
			//if it is the first time to be attacked set Ta with time stamp
			if (es->getTimeAttack() == -1)
				es->setTimeAttack(ts);
			templist.enqueue(es);
			if (es->getHealth() <= 0) {
				es->setTimeDead(ts);
				TheGame->killed(es);
			}
			else
				tlist.enqueue(es);
		}
	}
	//if number of earth soliders is less than attack capacity
	//attack all earth soliders available
	else {
		//loop to attack earth soliders from list
		for (int i{}; i < ES_attacked.getCount(); i++) {
			ES_attacked.dequeue(es);
			int damage = (power * health / 100) / sqrt(es->getHealth());
			es->setHealth(es->getHealth() - damage);
			//if it is the first time to be attacked set Ta with time stamp
			if (es->getTimeAttack() == -1)
				es->setTimeAttack(ts);
			templist.enqueue(es);
			if (es->getHealth() <= 0) {
				es->setTimeDead(ts);
				TheGame->killed(es);
			}
			else
				tlist.enqueue(es);
		}
	}
	//return alive earth soliders to earth solider list
	//add them to templist to be returned
	while (tlist.dequeue(estemp)) {
		TheGame->getEarthArmy()->addUnit(estemp);
	}
	return true;
}
