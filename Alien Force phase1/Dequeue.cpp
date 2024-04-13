#include "Dequeue.h"
#include "Node.h"

//sets front and back ptrs to null by default
//dequeue is empty by default
Dequeue::Dequeue()
{
	frontPtr = nullptr;
	backPtr = nullptr;
}

//checks if dequeue is empty 
//returns 1 if empty, 0 otherwise
bool Dequeue::isEmpty() const
{
	return (frontPtr==nullptr);
}

//standard enqueue from the back of queue
//returns 0 only if new drone cannot be allocated 
//1 otherwise
bool Dequeue::enqueue(const AlienDrone*& newDrone)
{
	Node<AlienDrone*>* newdrone = new Node<AlienDrone*>(const_cast<AlienDrone*>(newDrone));
	if (!newdrone)
		return false;
	if (isEmpty())
		frontPtr = newdrone;
	else
		backPtr->setNext(newdrone);

	backPtr = newdrone;
	count++;
	return true;
}

//enqueues from the front of queue
//returns 0 only if new drone cannot be allocated 
//1 otherwise
bool Dequeue::enqueueFront(AlienDrone*& newDrone)
{
	Node<AlienDrone*>* newdrone = new Node<AlienDrone*>(newDrone);
	if (!newdrone)
		return false;
	if (isEmpty())
		backPtr = newdrone;
	else
		newdrone->setNext(frontPtr);
	frontPtr = newdrone;
	count++;
	return true;
}

//dequeues from front
//returns 0 if dequeue is empty
//returns 1 otherwise and sets frontDrone pointer to drone removed
bool Dequeue::dequeue(AlienDrone*& frontDrone)
{
	if (isEmpty())
		return false;
	Node<AlienDrone*>* dronetodelete = frontPtr;
	frontDrone = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	if (dronetodelete == backPtr)
		backPtr = nullptr;

	dronetodelete->setNext(nullptr);
	delete dronetodelete;
	count--;
	return true;
}

bool Dequeue::dequeueBack(AlienDrone*& backDrone)
{
	if (isEmpty())
		return false;

	Node<AlienDrone*>* prevPtr = frontPtr;
	Node<AlienDrone*>* dronetodelete = backPtr;
	backDrone = backPtr->getItem();
	//if last node is only node
	if (prevPtr == dronetodelete) {
		frontPtr = nullptr;
		backPtr = nullptr;
		delete dronetodelete;
		count--;
		return true;
	}

	while (prevPtr->getNext() != dronetodelete)
		prevPtr = prevPtr->getNext();

	prevPtr->setNext(nullptr);
	backPtr = prevPtr;

	delete dronetodelete;
	count--;
	return true;
}

//peeks at first drone with out removing it
bool Dequeue::peek(AlienDrone*& frontDrone) const
{
	if (isEmpty()) return false;
	frontDrone = frontPtr->getItem();
	return true;
}

//peeks at last drone with out removing it
bool Dequeue::peekBack(AlienDrone*& backDrone)
{
	if (isEmpty()) return false;
	backDrone = backPtr->getItem();
	return true;
}

//prints in standard queue order
void Dequeue::print()
{
	if (isEmpty())
		return;
	Node<AlienDrone*>* printptr = frontPtr;
	cout << "[";
	while (printptr) {
		cout << printptr << ",";
		printptr = printptr->getNext();
	}
	cout << "]" << endl;
	return;
}

int Dequeue::getCount()
{
	return count;
}

//copy constructor for dequeue
Dequeue::Dequeue(Dequeue& DQ)
{
	frontPtr = backPtr = nullptr;
	Node<AlienDrone*>* copyDrone = DQ.frontPtr;
	AlienDrone* tempdrone = nullptr;
	while (copyDrone) {
		tempdrone = copyDrone->getItem();
		enqueue(tempdrone);
		copyDrone = copyDrone->getNext();
	}
}

//destructor
Dequeue::~Dequeue()
{
	AlienDrone* temp = frontPtr->getItem();
	while (temp)
		dequeue(temp);
}

