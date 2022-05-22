//Melisa DEMÝRHAN 
//Özge KATIRCI 
#include <iostream>
#include "Deque.h"
using namespace std;

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	head = tail = NULL;
	noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	free(head);
	free(tail);
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode* p = new DequeNode(item);
	if (head == NULL) {
		head = tail = p;
	}
	else {
		p->next = head;
		head->prev = p;
		head = p;
	}
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode* p = new DequeNode(item);
	if (tail == NULL) {
		head = tail = p;
	}
	else {
		p->prev = tail;
		tail->next = p;
		tail = p;
	}
	
	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (IsEmpty())
	{
		throw std::exception("Deque is empty");
	}
	int a = head->item;
	DequeNode* p = head;
	head = head->next;
	if (head == NULL)
	{
		tail = NULL;
	}
	else
	{
		head->prev = NULL;
	}
	delete[] p;
	noOfItems--;

	return a;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (IsEmpty())
	{
		throw std::exception("Deque is empty");
	}
	int a = tail->item;
	DequeNode* p = tail;
	tail = tail->prev;
	if (tail == NULL)
	{
		head = NULL;
	}
	else
	{
		tail->next = NULL;
	}
	delete[] p;
	noOfItems--;

	return a;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (IsEmpty()) {
		throw std::exception("Deque is empty");
	}
	return head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (IsEmpty()) {
		throw std::exception("Deque is empty");
	}
	return tail->item;
} //end-Rear

