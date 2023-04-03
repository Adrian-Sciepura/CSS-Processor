#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "ForwardList.h"
#include "Attribute.h"
#include "String.h"
#include "Section.h"

class ListNode
{
public:
	static constexpr int ARRAY_SIZE = 8;
	int numberOfSections;
	int cursor;
	ListNode* previous;
	ListNode* next;
	Section* sections[ARRAY_SIZE];

	ListNode();
	~ListNode();
};

#endif