#pragma once
#include "unit.h"
#include "LinkedQueue.h"
#include "AlienArmy.h"
#include "EarthArmy.h"
#include "randGen.h"

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
};

