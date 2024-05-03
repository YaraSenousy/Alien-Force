#pragma once
#include "unit.h"
#include "LinkedQueue.h"
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "randGen.h"
#include <fstream>
#include <sstream>

class Game
{
private:
	LinkedQueue <unit*> KilledList;
	AlienArmy alien_army;
	EarthArmy earth_army;
	randGen RandGen;
	int ESK, EGK, ETK, ASK, ADK, AMK; //count killed of each type
public:
	Game();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	randGen* getRandGen();
	void print(int TS);
	void LoadFromFile(string filename);
	void testcode();
	bool killed(unit*); //add unit to killed list
};

