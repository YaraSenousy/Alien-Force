#include "MonsterArray.h"
#include <iostream>
#include <ctime>
using namespace std;

MonsterArray::MonsterArray()
{
	count = 0;
}

bool MonsterArray::isEmpty() const
{
	return (count == 0);
}

bool MonsterArray::push(AlienMonster* alien)
{
	//checking that the array isnt full
	if (count == MAX_SIZE) return false;
	//adding the item and incrementing the count
	items[count] = alien;
	count++;
	return true;
}

bool MonsterArray::pop(AlienMonster*& random)
{
	//checkin that the array isnt empty
	if (isEmpty()) return false;
	//generating random index from 0 to count-1 (the last entry)
	srand((int)time(0));
	int randomIndex = rand()%(count-1);
	//returning the random item
	random = items[randomIndex];
	//switching the last element to the random index
	items[randomIndex] = items[count];
	//decrementing the count
	count--;
	return true;
}

bool MonsterArray::peek(AlienMonster*& random) const
{
	if (isEmpty()) return false;
	//generating random index from 0 to count-1 (the last entry)
	srand((int)time(0));
	int randomIndex = rand() % (count - 1);
	//returning the random item
	random = items[randomIndex];
	return true;
}

int MonsterArray::getCount()
{
	return count;
}

void MonsterArray::print()
{
	if (isEmpty()) return;
	cout << "[";
	for (int i{}; i < count; i++) {
		cout << items[i] << ",";
	}
	cout << "]";
}




