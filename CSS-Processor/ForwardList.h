#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "ForwardListNode.h"
#include <iostream>

template <class T>
class ForwardList
{
private:
	void newNode();

public:
	int numberOfNodes;
	ForwardListNode<T>* first;
	ForwardListNode<T>* last;
		
	ForwardList();
	~ForwardList();

	ForwardListNode<T>* find(const T& element);
	ForwardListNode<T>* find(int index);
	void add(const T& element);
	void add(T&& element);
	bool remove(const T& element);
};

template <class T>
ForwardList<T>::ForwardList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->numberOfNodes = 0;
}

template <class T>
ForwardList<T>::~ForwardList()
{
	ForwardListNode<T>* temp = this->first;
	ForwardListNode<T>* temp2;
	while (temp != nullptr)
	{
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

template <class T>
void ForwardList<T>::newNode()
{
	ForwardListNode<T>* temp = this->last;
	this->last = new ForwardListNode<T>();
	if (temp != nullptr)
		temp->next = this->last;
	else
		this->first = this->last;

	this->numberOfNodes++;
}

template<class T>
ForwardListNode<T>* ForwardList<T>::find(const T& element)
{
	ForwardListNode<T>* search = this->first;
	while (search != nullptr)
	{
		if (search->data == element)
			return search;
		search = search->next;
	}
	return nullptr;
}

template<class T>
ForwardListNode<T>* ForwardList<T>::find(int index)
{
	if(index > this->numberOfNodes - 1)
		return nullptr;

	ForwardListNode<T>* search = this->first;
	for (int i = 0; i < index; i++)
		search = search->next;

	return search;
}

template <class T>
void ForwardList<T>::add(const T& element)
{
	ForwardListNode<T>* whereToAdd = this->find(element);
	if (whereToAdd == nullptr)
	{
		newNode();
		whereToAdd = this->last;
	}

	whereToAdd->data = element;
}

template <class T>
void ForwardList<T>::add(T&& element)
{
	ForwardListNode<T>* whereToAdd = this->find(element);
	if (whereToAdd == nullptr)
	{
		newNode();
		whereToAdd = this->last;
	}
	
	whereToAdd->data = static_cast<T&&>(element);
}

template<class T>
bool ForwardList<T>::remove(const T& element)
{
	ForwardListNode<T>* search = this->first;
	ForwardListNode<T>* prev = nullptr;

	while (search != nullptr)
	{
		if (search->data == element)
		{
			if (prev == nullptr)
				this->first = search->next;
			else
				prev->next = search->next;

			if (search->next == nullptr)
				this->last = prev;

			delete search;
			this->numberOfNodes--;
			return true;
		}

		prev = search;
		search = search->next;
	}
	
	return false;
}

#endif