#include "Game.h"
#include <ctime>

void Game::testcode()
{
	srand((int)time(0));
	LoadFromFile("input.txt");
	for (int time{ 1 }; time <= 50; time++) {
		RandGen.AssignGenerated(time);
		int x = 1 + (rand() % 100);
		if (x < 10) {
			EarthSolider* ES;
			if (earth_army.getESlist().dequeue(ES))
				earth_army.addUnit(ES);
		}
		else if (x < 20) {
			EarthTank* ET;
			if (earth_army.getETlist().pop(ET));
				KilledList.enqueue(ET);
		}
		else if (x < 30) {
			EarthGunnery* EG;
			int pri;
			if (earth_army.getEGlist().dequeue(EG, pri)) {
				int health = EG->getHealth();
				EG->setHealth(health / 2);
				earth_army.addUnit(EG);
			}
		}
		else if (x < 40) {
			AlienSolider* AS;
			LinkedQueue<AlienSolider*> templist;
			for (int i{}; i < 5; i++) {
				if (alien_army.getASlist().dequeue(AS)) {
					int health = AS->getHealth();
					AS->setHealth(health - 20);
					templist.enqueue(AS);
				}
			}
			while (templist.dequeue(AS))
				alien_army.addUnit(AS);
		}
		else if (x < 50) {
			AlienMonster* AM;
			for (int i{}; i < 5; i++) {
				if (alien_army.getAMlist().pop(AM))
					alien_army.addUnit(AM);
			}
		}
		else if (x < 60) {
			for (int i{}; i < 3; i++) {
				AlienDrone* AD1;
				AlienDrone*	AD2;
				//make sure that there are 2 drones in the list
				if (alien_army.getADlist().dequeue(AD1)) 
					KilledList.enqueue(AD1);
				if (alien_army.getADlist().dequeueBack(AD2))
					KilledList.enqueue(AD2);
			}
		}
		print(time);
	}
}