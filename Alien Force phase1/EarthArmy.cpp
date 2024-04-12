#include "EarthArmy.h"
#include "unit.h"

void EarthArmy::addUnit(unit* u)
{
	u->setID(EarthCounter);
	EarthCounter++;
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
	cout << ET.getCount() << " ET ";
	ET.print();
	cout << EG.getCount() << " EG ";
	EG.print();

}
