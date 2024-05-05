#include "AlienMonster.h"
#include "Game.h"
bool AlienMonster::attack(LinkedQueue<unit*>&templist ,int ts)
{
	//get pointers to both lists
	ArrayStack<EarthTank*> listET= TheGame->getEarthArmy()->getETlist();
	LinkedQueue<EarthSolider*> listES =TheGame->getEarthArmy()->getESlist();

	//return false if both lists are empty
	if (listET.isEmpty()&&listES.isEmpty()) {
		return false;
	}

	//get count of units available to be attacked
	int ETtoAttack = listET.getCount();
	int EStoAttack = listES.getCount();

	//divide attack capacity amongst both lists
	int attack1 = ceil(attack_cap / 2);
	int attack2 = attack_cap / 2;

	//initialise pointers and lists to be used
	EarthTank* et = nullptr;
	EarthSolider* es = nullptr;
	ArrayStack<EarthTank*> tempETlist;
	LinkedQueue<EarthSolider*> tempESlist;

	//initialise counter for attacks and set them with
	//smallest bet. attack per list and units available to
	//be attacked
	int ETcounter = 0;
	int EScounter = 0;

	if (ETtoAttack > EStoAttack) {
		ETcounter = min(attack1, ETtoAttack);
		EScounter = min(attack2, EStoAttack);
	}
	else {
		ETcounter = min(attack2, ETtoAttack);
		EScounter = min(attack1, EStoAttack);
	}
	
	//attack Earth Tank; send to kill list if new health is less 
	//than 0 and send to templist otherwise
	for (int i{}; i < ETcounter; i++) {
		listET.pop(et);
		int damageET = float(power * (health / 100)) / sqrt(et->getHealth());
		et->setHealth(et->getHealth() - damageET);
		templist.enqueue(et);
		if (et->getHealth() <= 0) {
			TheGame->killed(et);
			et->setTimeDead(ts);
		}
		else {
			tempETlist.push(et);
		}
	}

	//attack Earth Solider; send to kill list if new health is less 
	//than 0 and send to templist otherwise
	for (int i{}; i < EScounter; i++) {
		listES.dequeue(es);
		int damageES = float(power * (health / 100)) / sqrt(es->getHealth());
		es->setHealth(es->getHealth() - damageES);
		templist.enqueue(es);
		if (es->getHealth() <= 0) {
			TheGame->killed(es);
			es->setTimeDead(ts);
		}
		else {
			tempESlist.enqueue(es);
		}
	}
	
	//continue attacking if there is remaining capacity
	int remainingCap = attack_cap - ETcounter - EScounter;
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
		else if (!listES.isEmpty()) {
			listES.dequeue(es);
			int damageES = float(power * (health / 100)) / sqrt(es->getHealth());
			es->setHealth(es->getHealth() - damageES);
			templist.enqueue(es);
			if (es->getHealth() <= 0) {
				es->setTimeDead(ts);
				TheGame->killed(es);
			}
			else {
				tempESlist.enqueue(es);
			}
		}
		remainingCap--;
	}

	//return alive units to their original lists
	while (tempETlist.pop(et)) {
		TheGame->getEarthArmy()->addUnit(et);
	}
	while (tempESlist.dequeue(es)) {
		TheGame->getEarthArmy()->addUnit(es);
	}
	return true;
}
