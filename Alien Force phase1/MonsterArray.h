#pragma once
#include "AlienMonster.h"
class MonsterArray
{
	enum { MAX_SIZE = 100 };
	AlienMonster* items[MAX_SIZE];
	int count;
public:
	MonsterArray();
	bool isEmpty() const;
	bool push(AlienMonster*);
	bool pop(AlienMonster*&);
	bool peek(AlienMonster*&) const;
	int getCount();
	void print();
};

