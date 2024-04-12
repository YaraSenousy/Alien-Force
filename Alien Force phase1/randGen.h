#ifndef RAND_GEN
#define RAND_GEN
#include "unit.h"
class Game;

class randGen
{
private:
	Game* TheGame;
	int N,ET,EG,ES,AS,AD,AM,prob;
	int minEHealth,maxEHealth,minEPower,maxEPower,minECap,maxECap;
	int minAHealth, maxAHealth, minAPower, maxAPower, minACap, maxACap;
public:
	randGen(Game* game);
	unit* CreateUnit(int timestep,int B,int type=1);
	void Func(int timestep);
};
#endif

