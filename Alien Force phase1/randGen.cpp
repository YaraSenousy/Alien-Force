#include "randGen.h"
#include "Game.h"
#include <ctime>

//sets game pointer
randGen::randGen(Game* game)
{
	TheGame = game;
}

//parameters: timestep to add unit 
// randomly generated int B to determine which type of unit to add in reference to distributions from input file
//int type to determine earth unit or alien unit
unit* randGen::CreateUnit(int timestep,int B,int type)
{
	unit* Unit;
	if (type == 1) {
		int health = minEHealth + (rand() % maxEHealth); //generate random health within range from input file
		int power = minEPower + (rand() % maxEPower); //generate random power within range from input file
		int cap = minECap + (rand() % maxECap); //generate random capacity within range from input file
		if (B <= ES) {
			Unit = new EarthSolider(timestep, health, power, cap);
		}
		else if (B <= (ES + ET)) {
			Unit = new EarthTank(timestep, health, power, cap);
		}
		else if (B <= (ES + ET + EG)) {
			Unit = new EarthGunnery(timestep, health, power, cap);
		}
	}
	else {
		int health = minAHealth + (rand() % maxAHealth); //generate random health within range from input file
		int power = minAPower + (rand() % maxAPower); //generate random power within range from input file
		int cap = minACap + (rand() % maxACap); //generate random capacity within range from input file
		if (B <= AS) {
			Unit = new AlienSolider(timestep, health, power, cap);
		}
		else if (B <= (AS + AM)) {
			Unit = new AlienMonster(timestep, health, power, cap);
		}
		else if (B <= (AS + AM + AD)) {
			Unit = new AlienDrone(timestep, health, power, cap);
		}
	}
	return Unit;
}

void randGen::Func(int timestep)
{
	srand((int)time(0));
	int A = 1 + (rand() % 100);
	if (A <= prob) {
		unit* temp;
		int B = 1 + (rand() % 100);
		for (int i{}; i < N; i++) {
			temp = CreateUnit(timestep, B);
			
		}
		for (int i{}; i < N; i++) {
			temp = CreateUnit(timestep, B,2);
		}
	}
}
