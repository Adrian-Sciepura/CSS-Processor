#include "List.h"

void List::newNode()
{
	ListNode* temp = this->last;
	this->last = new ListNode();
	this->last->previous = temp;
	
	if (temp != nullptr)
		temp->next = this->last;
	else
		this->first = this->last;

	this->numberOfNodes++;
}

void List::removeNode(ListNode* node)
{
	if (this->numberOfNodes == 1)
	{
		this->first = nullptr;
		this->last = nullptr;
	}
	else if (node == this->first)
	{
		this->first = node->next;
		node->next->previous = this->first;
	}
	else if (node == this->last)
	{
		this->last = node->previous;
		node->previous->next = nullptr;
	}
	else
	{
		node->previous->next = node->next;
		node->next->previous = node->previous;
	}

	this->numberOfNodes--;
	delete node;
}

Tuple<ListNode*, int> List::getSection(int index)
{
	if (index > this->numberOfSections - 1)
		return { nullptr, NULL };

	ListNode* node = this->first;
	int counter = node->numberOfSections;

	while (counter <= index)
	{
		node = node->next;
		counter += node->numberOfSections;
	}

	int n = index - (counter - node->numberOfSections);
	int i = -1, j = -1;
	
	while (i < n)
	{
		i++;
		j++;
		if (node->sections[j] == nullptr)
			i--;
	}
	
	return { node, j };
}

List::List()
{
	this->first = nullptr;
	this->last = nullptr;
	this->numberOfNodes = 0;
	this->numberOfSections = 0;
}

List::~List()
{
	ListNode* temp = this->first;
	ListNode* temp2;
	while (temp != nullptr)
	{
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

Section* List::newSection()
{
	if (this->last == nullptr || this->last->cursor == ListNode::ARRAY_SIZE)
		this->newNode();
	
	this->last->sections[this->last->cursor] = new Section();
	this->last->cursor++;
	this->last->numberOfSections++;
	this->numberOfSections++;
	return this->last->sections[this->last->cursor - 1];
}

bool List::removeSection(int index)
{
	if (index > numberOfSections-1)
		return false;

	Tuple<ListNode*, int> result = this->getSection(index);
	ListNode* node = result.first;
	int i = result.second;
	delete node->sections[i];
	node->sections[i] = nullptr;
	node->numberOfSections--;
	this->numberOfSections--;

	if (node->numberOfSections == 0)
		this->removeNode(node);

	return true;
}

int List::countSelectorOccurrences(const String& selectorName)
{
	int counter = 0;
	ListNode* node = this->first;
	Section* section = nullptr;
	while (node != nullptr)
	{
		for (int i = 0; i < node->cursor; i++)
		{
			section = node->sections[i];
			if (section != nullptr)
				if (section->selectors.find(selectorName) != nullptr)
					counter += 1;
		}

		node = node->next;
	}

	return counter;
}

int List::countAttributeOccurrences(const String& attributeName)
{
	int counter = 0;
	Attribute attributeToFind = { attributeName, "" };
	ListNode* node = this->first;
	Section* section = nullptr;
	while (node != nullptr)
	{
		for (int i = 0; i < node->cursor; i++)
		{
			section = node->sections[i];
			if (section != nullptr)
				if (section->attributes.find(attributeToFind) != nullptr)
					counter += 1;
		}

		node = node->next;
	}

	return counter;
}

Section* List::operator[](int index)
{
	Tuple<ListNode*, int> temp = this->getSection(index);
	if(temp.first == nullptr)
		return nullptr;

	return temp.first->sections[temp.second];
}
