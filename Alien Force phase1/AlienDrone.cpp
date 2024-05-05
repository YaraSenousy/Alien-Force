#include "AlienDrone.h"
#include "Game.h"
bool AlienDrone::attack(LinkedQueue<unit*>& templist,int ts)
{
	//assuming function is only called if count >=2
	//get pointers to both lists
	ArrayStack<EarthTank*> listET = TheGame->getEarthArmy()->getETlist();
	priQueue<EarthGunnery*> listEG = TheGame->getEarthArmy()->getEGlist();

	//return false if both lists are empty
	if (listET.isEmpty() && listEG.isEmpty()) {
		return false;
	}

	//get count of units available to be attacked
	int ETtoAttack = listET.getCount();
	int EGtoAttack = listEG.getCount();

	//divide attack capacity amongst both lists
	int attack1 = ceil(attack_cap / 2);
	int attack2 = attack_cap / 2;

	//initialise pointers and lists to be used
	EarthTank* et = nullptr;
	EarthGunnery* eg = nullptr;
	ArrayStack<EarthTank*> tempETlist;
	priQueue<EarthGunnery*> tempEGlist;

	//initialise counter for attacks and set them with
	//smallest bet. attack per list and units available to
	//be attacked
	int ETcounter = 0;
	int EGcounter = 0;

	if (ETtoAttack > EGtoAttack) {
		ETcounter = min(attack1, ETtoAttack);
		EGcounter = min(attack2, EGtoAttack);
	}
	else {
		ETcounter = min(attack2, ETtoAttack);
		EGcounter = min(attack1, EGtoAttack);
	}

	//attack Earth Tank; send to kill list if new health is less 
	//than 0 and send to templist otherwise
	for (int i{}; i < ETcounter; i++) {
		listET.pop(et);
		int damageET = float(power * (health / 100)) / sqrt(et->getHealth());
		et->setHealth(et->getHealth() - damageET);
		templist.enqueue(et);
		if (et->getHealth() <= 0) {
			et->setTimeDead(ts);
			TheGame->killed(et);
		}
		else {
			tempETlist.push(et);
		}
	}

	int pri = 0;
	//attack Earth Gunnery; send to kill list if new health is less 
	//than 0 and send to templist otherwise
	for (int i{}; i < EGcounter; i++) {
		listEG.dequeue(eg,pri);
		int damageEG = float(power * (health / 100)) / sqrt(eg->getHealth());
		eg->setHealth(eg->getHealth() - damageEG);
		templist.enqueue(eg);
		if (eg->getHealth() <= 0) {
			eg->setTimeDead(ts);
			TheGame->killed(eg);
		}
		else {
			tempEGlist.enqueue(eg, pri);
		}
	}

	//continue attacking if there is remaining capacity
	int remainingCap = attack_cap - ETcounter - EGcounter;
	while (remainingCap > 0) {
		if (!listET.isEmpty()) {
			listET.pop(et);
			int damageET = float(power * (health / 100)) / sqrt(et->getHealth());
			et->setHealth(et->getHealth() - damageET);
			templist.enqueue(et);
			if (et->getHealth() <= 0) {
				et->setTimeDead(ts);
				TheGame->killed(et);
			}
			else {
				tempETlist.push(et);
			}
		}
		else if (!listEG.isEmpty()) {
			listEG.dequeue(eg, pri);
			int damageEG = float(power * (health / 100)) / sqrt(eg->getHealth());
			eg->setHealth(eg->getHealth() - damageEG);
			templist.enqueue(eg);
			if (eg->getHealth() <= 0) {
				eg->setTimeDead(ts);
				TheGame->killed(eg);
			}
			else {
				tempEGlist.enqueue(eg, pri);
			}
		}
		remainingCap--;
	}

	//return alive units to their original lists
	while (tempETlist.pop(et)) {
		TheGame->getEarthArmy()->addUnit(et);
	}
	while (tempEGlist.dequeue(eg,pri)) {
		TheGame->getEarthArmy()->addUnit(eg);
	}
	return true;

}
