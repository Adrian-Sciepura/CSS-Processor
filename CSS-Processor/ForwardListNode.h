#ifndef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H

template <class T>
class ForwardListNode
{
public:
	static constexpr int ARRAY_SIZE = 8;
	int storedStructures;
	ForwardListNode<T>* next;
	T* data;

	ForwardListNode();
	~ForwardListNode();
};

template <class T>
ForwardListNode<T>::ForwardListNode()
{
	this->data = new T[ARRAY_SIZE];
	this->storedStructures = 0;
	this->next = nullptr;
}

template <class T>
ForwardListNode<T>::~ForwardListNode()
{
	delete[] this->data;
}

#endif