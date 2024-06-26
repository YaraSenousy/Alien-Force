#include "randGen.h"
#include "Game.h"
#include <ctime>


randGen::randGen()
{
	EarthCounter = 1;
	AlienCounter = 2000;
}

//parameters: timestep to add unit 
// randomly generated int B to determine which type of unit to add in reference to distributions from input file
//int type to determine earth unit or alien unit
unit* randGen::CreateUnit(int timestep,int B,int type)
{
	unit* Unit = nullptr;
	if (type == 1) {
		int health = minEHealth + (rand() % (maxEHealth - minEHealth + 1)); //generate random health within range from input file
		int power = minEPower + (rand() % (maxEPower - minEPower + 1)); //generate random power within range from input file
		int cap = minECap + (rand() % (maxECap - minECap + 1)); //generate random capacity within range from input file
		if (B <= ES) {
			Unit = new EarthSolider(timestep, health, power, cap, TheGame);
		}
		else if (B <= (ES + ET)) {
			Unit = new EarthTank(timestep, health, power, cap, TheGame);
		}
		else if (B <= (ES + ET + EG)) {
			Unit = new EarthGunnery(timestep, health, power, cap, TheGame);
		}
		Unit->setID(EarthCounter);
		EarthCounter++;
	}
	else {
		int health = minAHealth + (rand() % (maxAHealth - minAHealth + 1)); //generate random health within range from input file
		int power = minAPower + (rand() % (maxAPower - minAPower + 1)); //generate random power within range from input file
		int cap = minACap + (rand() % (maxACap - minACap + 1)); //generate random capacity within range from input file
		if (B <= AS) {
			Unit = new AlienSolider(timestep, health, power, cap, TheGame);
		}
		else if (B <= (AS + AM)) {
			Unit = new AlienMonster(timestep, health, power, cap, TheGame);
		}
		else if (B <= (AS + AM + AD)) {
			Unit = new AlienDrone(timestep, health, power, cap, TheGame);
		}
		Unit->setID(AlienCounter);
		AlienCounter++;
	}
	return Unit;
}

void randGen::AssignGenerated(int timestep) //generate earth and army units for a given time step
{
	int A = 1 + (rand() % 100);
	if (A <= prob) {
		unit* temp;
		for (int i{}; i < N; i++) {
			int B = 1 + (rand() % 100);
			temp = CreateUnit(timestep, B);
			TheGame->getEarthArmy()->addUnit(temp);
		}
		for (int i{}; i < N; i++) {
			int B = 1 + (rand() % 100);
			temp = CreateUnit(timestep, B,2);
			TheGame->getAlienArmy()->addUnit(temp);
		}
	}
}

void randGen::setGame(Game* g)
{
	TheGame = g;
}

void randGen::setN(int n)
{
	N = n;
}

void randGen::setET(int et)
{
	ET = et;
}

void randGen::setEG(int eg)
{
	EG = eg;
}

void randGen::setES(int es)
{
	ES = es;
}

void randGen::setAS(int as)
{
	AS = as;
}

void randGen::setAD(int ad)
{
	AD = ad;
}

void randGen::setAM(int am)
{
	AM = am;
}

void randGen::setProb(int p)
{
	prob = p;
}

void randGen::setEH(int minEH, int maxEH)
{
	minEHealth = minEH;
	maxEHealth = maxEH;
}

void randGen::setEP(int minEP, int maxEP)
{
	minEPower = minEP;
	maxEPower = maxEP;
}

void randGen::setEC(int minEC, int maxEC)
{
	minECap = minEC;
	maxECap = maxEC;
}

void randGen::setAH(int minAH, int maxAH)
{
	minAHealth = minAH;
	maxAHealth = maxAH;
}

void randGen::setAP(int minAP, int maxAP)
{
	minAPower = minAP;
	maxAPower= maxAP;
}

void randGen::setAC(int minAC, int maxAC)
{
	minACap = minAC;
	maxACap = maxAC;
}