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
	unit* CreateUnit(int timestep,int B,int type=1);
	void AssignGenerated(int timestep);
	void setGame(Game* g);
	void setN(int n);
	void setET(int et);
	void setEG(int eg);
	void setES(int es);
	void setAS(int as);
	void setAD(int ad);
	void setAM(int am);
	void setProb(int p);
	void setEH(int minEH, int maxEH);//sets minimum and maximum earth health
	void setEP(int minEP, int maxEP);//sets minimum and maximum earth power
	void setEC(int minEC, int maxEC);// sets minimum and maximum earth capacity
	void setAH(int minAH, int maxAH);//sets minimum and maximum alien health
	void setAP(int minAP, int maxAP);//sets minimum and maximum alien power
	void setAC(int minAC, int maxAC);// sets minimum and maximum alien capacity
};
#endif

