#ifndef DEQUEUE
#define DEQUEUE
#include "LinkedQueue.h"

#include "AlienDrone.h"

class Dequeue : public LinkedQueue<AlienDrone*>
{
private:
	Node<AlienDrone*>* frontPtr; //pointer to head of dequeue
	Node<AlienDrone*>* backPtr; //pointer to end of dequeue
	int count; //length of dequeue
public:
	Dequeue();
	bool isEmpty() const; 
	//bool enqueue(AlienDrone*& newEntry); //standard enqueue from the end of queue
	bool enqueueFront(AlienDrone* newDrone); //enqueue from the front of queue
	//bool dequeue(AlienDrone*& frontDrone); //standard dequeue front
	bool dequeueBack(AlienDrone*& backDrone); //dequeue from the end of queue
	//bool peek(AlienDrone*& frontDrone) const; //standard peek front
	bool peekBack(AlienDrone*& backDrone) ; //peek at end of queue
	//void print(); //prints in standard sequence of queue
	//int getCount();
	Dequeue(Dequeue& DQ); //copy constructor

	virtual ~Dequeue(); //destructor
};
#endif



