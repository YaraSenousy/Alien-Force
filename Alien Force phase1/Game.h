#pragma once
#include "unit.h"
#include "LinkedQueue.h"
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "randGen.h"
#include <fstream>

class Game
{
private:
	LinkedQueue <unit*> KilledList;
	AlienArmy alien_army;
	EarthArmy earth_army;
	randGen RandGen;
public:
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	randGen* getRandGen();
	void print();
	void LoadFromFile(string filename);
};

