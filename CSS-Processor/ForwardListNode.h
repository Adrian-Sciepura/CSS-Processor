#ifndef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H

template <class T>
class ForwardListNode
{
public:
	ForwardListNode<T>* next;
	T data;

	ForwardListNode();
	~ForwardListNode();
};

template <class T>
ForwardListNode<T>::ForwardListNode()
{
	this->next = nullptr;
}

template <class T>
ForwardListNode<T>::~ForwardListNode()
{

}

#endif