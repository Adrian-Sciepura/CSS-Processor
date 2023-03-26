#include "List.h"

List::List()
{
	this->first = nullptr;
	this->last = nullptr;
	this->numberOfNodes = 0;
}

List::~List()
{
	ListNode* temp = this->first;
	ListNode* temp2;
	while (true)
	{
		if (temp == nullptr)
			break;

		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

void List::newNode()
{
	ListNode* temp = this->last;
	this->last = new ListNode();
	
	if (temp != nullptr)
		temp->next = this->last;
	else
		this->first = this->last;

	this->last->previous = temp;
	this->numberOfNodes++;
}

ListNode* List::getNode(int index)
{
	if (index > numberOfNodes - 1)
		return nullptr;

	ListNode* search = this->first;

	for (int i = 0; i < index; i++)
		search = search->next;

	return search;
}