#ifndef DEQUEUE
#define DEQUEUE
#include "QueueADT.h"
#include "Node.h"
#include "AlienDrone.h"

class Dequeue : public QueueADT<AlienDrone>
{
private:
	Node<AlienDrone>* frontPtr; //pointer to head of dequeue
	Node<AlienDrone>* backPtr; //pointer to end of dequeue
	int count; //length of dequeue
public:
	Dequeue();
	bool isempty() const; 
	bool enqueue(const AlienDrone& newDrone); //standard enqueue from the end of queue
	bool enqueueBack(const AlienDrone& newDrone); //enqueue from the front of queue
	bool dequeue(AlienDrone& frontDrone); //standard dequeue front
	bool dequeueBack(AlienDrone& backDrone); //dequeue from the end of queue
	bool peek(AlienDrone& frontDrone) const; //standard peek front
	bool peekBack(AlienDrone& backDrone) const; //peek at end of queue
	void print(); //prints in standard sequence of queue
	Dequeue(const Dequeue& DQ); //copy constructor

	virtual ~Dequeue();
};
#endif

inline Dequeue::Dequeue()
{
	frontPtr = nullptr;
	backPtr = nullptr;
}

inline bool Dequeue::isempty() const
{
	return (frontPtr==nullptr);
}

inline bool Dequeue::enqueue(const AlienDrone& newDrone)
{
	
}

