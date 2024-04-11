#ifndef DEQUEUE
#define DEQUEUE
#include "QueueADT.h"
#include "Node.h"
#include "AlienDrone.h"

class Dequeue : public QueueADT<AlienDrone*>
{
private:
	Node<AlienDrone*>* frontPtr; //pointer to head of dequeue
	Node<AlienDrone*>* backPtr; //pointer to end of dequeue
	int count; //length of dequeue
public:
	Dequeue();
	bool isEmpty(); 
	bool enqueue(AlienDrone*& newDrone); //standard enqueue from the end of queue
	bool enqueueFront( AlienDrone*& newDrone); //enqueue from the front of queue
	bool dequeue(AlienDrone*& frontDrone); //standard dequeue front
	bool dequeueBack(AlienDrone*& backDrone); //dequeue from the end of queue
	bool peek(AlienDrone*& frontDrone) ; //standard peek front
	bool peekBack(AlienDrone*& backDrone) ; //peek at end of queue
	void print(); //prints in standard sequence of queue
	Dequeue(Dequeue& DQ); //copy constructor

	virtual ~Dequeue(); //destructor
};
#endif

