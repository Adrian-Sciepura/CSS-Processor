#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "ForwardList.h"
#include "Attribute.h"
#include "String.h"

class ListNode
{
public:
	ListNode* previous;
	ListNode* next;
	ForwardList<Attribute> attributes;
	ForwardList<String> selectors;

	ListNode();
	~ListNode();
};

#endif