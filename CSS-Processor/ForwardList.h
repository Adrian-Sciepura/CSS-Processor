#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "ForwardListNode.h"
#include <iostream>

template <class T>
class ForwardList
{
public:
	ForwardListNode<T>* first;
		
	ForwardList();
	~ForwardList();

	void add(const T& element);
	void add(T&& element);
	void print();
};

template <class T>
ForwardList<T>::ForwardList()
{
	this->first = new ForwardListNode<T>();
}

template <class T>
ForwardList<T>::~ForwardList()
{
	ForwardListNode<T>* temp = first;
	ForwardListNode<T>* temp2;
	while (true)
	{
		temp2 = temp->next;
		delete temp;
		if (temp2 == nullptr)
			break;
	
		temp = temp2;
	}
}

template <class T>
void ForwardList<T>::add(const T& element)
{
	if (first->storedStructures == first->ARRAY_SIZE)
	{
		ForwardListNode<T>* temp = new ForwardListNode<T>();
		temp->next = this->first;
		this->first = temp;
	}

	first->data[first->storedStructures] = element;
	first->storedStructures++;
}

template <class T>
void ForwardList<T>::add(T&& element)
{
	if (first->storedStructures == first->ARRAY_SIZE)
	{
		ForwardListNode<T>* temp = new ForwardListNode<T>();
		temp->next = this->first;
		this->first = temp;
	}

	first->data[first->storedStructures] = static_cast<T&&>(element);
	first->storedStructures++;
}

template <class T>
void ForwardList<T>::print()
{
	int counter = 0;
	ForwardListNode<T>* node = first;

	while (true)
	{
		for (int i = 0; i < node->storedStructures; i++)
			std::cout << "Data from node " << counter << ": " << node->data[i] << '\n';

		std::cout << '\n';
		counter++;
		if (node->next == nullptr)
			break;

		node = node->next;
	}
}

#endif