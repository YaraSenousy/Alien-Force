#ifndef DEQUEUE
#define DEQUEUE
#include "QueueADT.h"
#include "Node.h"
template<Drone>
class Dequeue : public QueueADT<Drone>
{
private:
	Node<Drone>* frontPtr; //pointer to head of dequeue
	Node<Drone>* backPtr; //pointer to end of dequeue
	int count; //length of dequeue
public:
	Dequeue();
	bool isempty() const; 
	bool enqueue(const Drone& newDrone); //standard enqueue from the end of queue
	bool enqueueBack(const Drone& newDrone); //enqueue from the front of queue
	bool dequeue(Drone& frontDrone); //standard dequeue front
	bool dequeueBack(Drone& backDrone); //dequeue from the end of queue
	bool peek(Drone& frontDrone) const; //standard peek front
	bool peekBack(Drone& backDrone) const; //peek at end of queue
	void print(); //prints in standard sequence of queue
	Dequeue(const Dequeue& DQ); //copy constructor

	virtual ~Dequeue();
};
#endif

inline Dequeue<Drone>::Dequeue()
{
	frontPtr = nullptr;
	backPtr = nullptr;
}

inline bool Dequeue<Drone>::isempty() const
{
	return (frontPtr==nullptr);
}

inline bool Dequeue<>::enqueue(const Drone& newDrone)
{
	
}

