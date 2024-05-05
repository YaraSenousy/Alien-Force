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
	void print(int TS,int es,int et,int eg,int as,int ad1,int ad2,int am, LinkedQueue<unit*>& es_attacked, LinkedQueue<unit*>& et_attacked, LinkedQueue<unit*>& eg_attacked,LinkedQueue<unit*>& as_attacked, LinkedQueue<unit*>& ad_attacked, LinkedQueue<unit*>& am_attacked);
	void LoadFromFile(string filename);
	void SaveToFile(string filename,string result);
	void testcode();
	bool killed(unit*); //add unit to killed list
	void simulate();
	string status(bool& endgame,bool);
};

