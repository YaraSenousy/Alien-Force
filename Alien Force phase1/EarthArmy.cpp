#include "EarthArmy.h"
#include "unit.h"

void EarthArmy::addUnit(unit* u)
{
	if (u->getType() == "ES") {
		ES.enqueue(static_cast<EarthSolider*>(u));
	}
	else if (u->getType() == "ET") {
		ET.push(static_cast<EarthTank*> (u));
	}
	else if (u->getType() == "EG") {
		int priority = u->getPower() * (u->getHealth()/100);
		EG.enqueue(static_cast<EarthGunnery*> (u), priority);
	}
}


void EarthArmy::print()
{
	cout << "============== Earth Army Alive Units =================" << endl;
	cout << ES.getCount() << " ES ";
	ES.print();
	cout << endl << ET.getCount() << " ET ";
	ET.print();
	cout << endl << EG.getCount() << " EG ";
	EG.print();
	cout << endl;

}

LinkedQueue<EarthSolider*> &EarthArmy::getESlist()
{
	return ES;
}

ArrayStack<EarthTank*> &EarthArmy::getETlist()
{
	return ET;
}

priQueue<EarthGunnery*> &EarthArmy::getEGlist()
{
	return EG;
}

void EarthArmy::earth_attack(LinkedQueue<unit*>& es, LinkedQueue<unit*>& et, LinkedQueue<unit*>& eg, int ts)
{
	EarthSolider* es_attack;
	//pick a soldier to attack
	if (ES.peek(es_attack)) {
		es_attack->attack(es, ts);
		//if it is the first time to attack set Ta with time stamp
		if (es_attack->getTimeAttack() == -1)
			es_attack->setTimeAttack(ts);
	}
	EarthGunnery* eg_attack;
	int pri;
	//pick a gunnary to attack
	if (EG.peek(eg_attack,pri)) {
		eg_attack->attack(eg, ts);
		//if it is the first time to attack set Ta with time stamp
		if (eg_attack->getTimeAttack() == -1)
			eg_attack->setTimeAttack(ts);
	}
	EarthTank* et_attack;
	//pick a tank to attack
	if (ET.peek(et_attack)) {
		et_attack->attack(et, ts);
		//if it is the first time to attack set Ta with time stamp
		if (et_attack->getTimeAttack() == -1)
			et_attack->setTimeAttack(ts);
	}
}
