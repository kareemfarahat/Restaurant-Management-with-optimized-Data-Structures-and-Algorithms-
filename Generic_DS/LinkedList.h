#include "Node.h"
#include "..\Rest\Order.h"
#include"..\Defs.h"
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:
	void NullHead() {
		Head = nullptr;
	}


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}


	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}

	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}

	void InsertEnd(const T& data) {
		Node<T>* p = new Node <T>(data);
		Node <T>* q = Head;
		if (!Head)
			Head = p;
		else {
			while (q->getNext())
			{
				q = q->getNext();

			};
			q->setNext(p);
		}
	}
	bool FindID(int Key) {
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem()->getID() == Key)

				return true;
			p = p->getNext();

		}
		return false;
	}

	bool Find(T Key) {
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == Key)
				return true;
			else
			p = p->getNext();

		}
		return false;
	}

	void DeleteFirst() {
		if (Head)

		{
			Node <T>* p = Head;
			Head = Head->getNext();
			delete p;
			count--;
		}
		else
		{
			std::cout << "their is no items " << std::endl;
		}
	}

	void DeleteLast() {
		if (Head)
		{
			Node <T>* p = Head;
			while (p->getNext()->getNext())
			{
				p = p->getNext();
			}
			delete p->getNext();
			p->setNext(nullptr);
			count--;
		}
		else
		{
			std::cout << "the List is Empty " << std::endl;
		}

	}bool DeleteNode(T value) {

		if (Find(value))
		{
			
			Node<T>* p = Head;
if (!p->getNext()) {
	delete p;
	count--;
	Head = nullptr;
	return true;
}
else if (Head->getItem() == value) {
	Node<T>* Op = Head;
	Head = Op->getNext();
	delete Op;
	count--;
	return true;
}
else if (!p->getNext()->getNext()) {
	if (p->getItem() == value) {
		Head = p->getNext();
		delete p;
		return true;
	}
	else {
		delete p->getNext();
		p->setNext(nullptr);
		return true;
	}

}

else {

	while (p->getNext()->getItem() != value)
	{
		p = p->getNext();
	}
	Node<T>* q = p->getNext()->getNext();
	delete p->getNext();
	count--;
	p->setNext(q);
	return true;
}
		}
		else
		{
		//std::cout << value << "   Does not exist in the list   " << std::endl;
		return false;

		}
	}

	bool DeleteNodes(const T& value) {
		if (CountOccurance(value))
		{
			for (int i = CountOccurance(value); i > 0; i--)
			{
				DeleteNode(value);
				i--;
			}
			return true;
		}
		else return false;

	}
	Order** getNodes(int ctime) {
		
		Node<Order*>* R = Head;
		int c = 20,i = 0;
		
		if (!Head)
			return nullptr;
		else {
			while (R)
			{
				if (R->getItem()->getFinishTime() == ctime)
				{
					c++;
				}
				R = R->getNext();
			}
			Order** p = new Order * [c + 1];
			R=Head;
			if (!R->getNext()) {
				if (R->getItem()->getFinishTime() == ctime)
				{
					p[i] = R->getItem();
					delete R;
					Head = nullptr;
					p[1] = nullptr;
					return p;
				}
				else
					return nullptr;
			}

			else if (!R->getNext()->getNext()) {
				if (R->getItem()->getFinishTime() == ctime
					&& R->getNext()->getItem()->getFinishTime() != ctime) {
					p[i] = R->getItem();
					p[1] = nullptr;
					Node<T>* Op = Head;
					Head = Op->getNext();
					delete Op;
					count--;
					return p;
				}

				else if (R->getItem()->getFinishTime() != ctime
					&& R->getNext()->getItem()->getFinishTime() == ctime) {
					p[i] = R->getNext()->getItem();
					p[1] = nullptr;
					delete R->getNext();
					R->setNext(nullptr);
					count--;
					return p;
				}

				else if (R->getItem()->getFinishTime() == ctime
					&& R->getNext()->getItem()->getFinishTime() == ctime) {
					p[i] = R->getItem();
					p[1] = R->getNext()->getItem();
					p[2] = nullptr;
					delete R->getNext();
					delete R;
					Head = nullptr;
					count = 0;
					return p;
				}


				return nullptr;
			}
			else {
				while (R->getItem()->getFinishTime() == ctime) {
					p[i] = R->getItem();
					i++;
					Node<T>* Op = Head;
					Head = Op->getNext();
					delete Op;
					count--;
					if (!Head->getNext() && R->getItem()->getFinishTime() == ctime)
					{
						p[i] = Head->getItem();
						i++;
						delete Head;
						Head = nullptr;
						p[i] = nullptr;
						count--;
						return p;
					}
				}
				while (!R->getNext()->getNext())
				{
					if (R->getNext()->getItem()->getFinishTime() == ctime) {
						p[i] = R->getNext()->getItem();
						i++;
						Node<Order*>* op = R->getNext()->getNext();
						delete R->getNext();
						R->setNext(op);
						count--;
					}
					R = R->getNext();
				}
				p[i] = nullptr;
				return p;
			}
		}
		return nullptr;
	}

	Order* PeekPriority() {
		if (Head) {
			Node <Order*>* P = Head;
			Order* max = P->getItem()->getPriority();
			P = P->getNext();
			while (P->getNext())
			{
				if (max->getPriority()  < P->getItem()->getPriority()) {
					max = P->getItem();
					P = P->getNext();
				}
				else {
					P = P->getNext();
				}
			}
			return max;
		}
		
	}
	bool IsEmpty() {
		if (!Head)
			return true;
		else
			return false;
	}

	Order* getOrderType(ORD_TYPE type) {

		Node<Order*>* p = Head;
		while (p)
		{
			if (p->getItem()->GetType() == type) {
				Order* pO = p->getItem();
				DeleteNode(p->getItem());
				return pO;
			}
			else	
			p = p->getNext();

		}
		return nullptr;

	}


	Order* GetPriority() {
		
		if (Head) {
			Node <Order*>* P = Head;
			Order* max = P->getItem();
		
			if (P->getNext() == nullptr) {

				DeleteNode(max);
				return max;
			}
			
			else {
				
				while (P->getNext())
				{

					if (max->getPriority() <= P->getItem()->getPriority()) {
						max = P->getItem();
						P = P->getNext();
					}

					else
						P = P->getNext();
					
				}
				if (max->getPriority() < P->getItem()->getPriority())
					max = P->getItem();


				DeleteNode(max);
				return max;
			}


		}
		
		return nullptr;
	}

	

	T* ToArray(int& c) {
		c = 0;
		if (!Head)
			return nullptr;
		
		Node<T>* p = Head;
		while (p)
		{
			c++;
			p = p->getNext();
		}


		T* Arr = new T[c];
		p = Head;
		for (int i = 0; i < c; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
};
