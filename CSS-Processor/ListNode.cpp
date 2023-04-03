#include "ListNode.h"

ListNode::ListNode()
{
	this->previous = nullptr;
	this->next = nullptr;
	this->cursor = 0;
	this->numberOfSections = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
		this->sections[i] = nullptr;
}

ListNode::~ListNode()
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		if (sections[i] != nullptr)
			delete sections[i];
}
