#ifndef LIST_H
#define LIST_H

#include "ListNode.h"

class List
{
public:
	int numberOfNodes;
	ListNode* first;
	ListNode* last;

	List();
	~List();

	void newNode();
	ListNode* getNode(int index);
};

#endif