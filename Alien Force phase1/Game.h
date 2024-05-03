#pragma once
#include "unit.h"
#include "LinkedQueue.h"
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "randGen.h"
#include <fstream>
#include <sstream>

class unit;
class Game
{
private:
	LinkedQueue <unit*> KilledList;
	AlienArmy alien_army;
	EarthArmy earth_army;
	randGen RandGen;
public:
	Game();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	randGen* getRandGen();
	void print(int TS);
	void LoadFromFile(string filename);
	void testcode();
};

