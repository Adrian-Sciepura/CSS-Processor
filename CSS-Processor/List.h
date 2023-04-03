#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include "Tuple.h"

class List
{
private:
	void newNode();
	void removeNode(ListNode* node);

public:
	int numberOfNodes;
	int numberOfSections;
	ListNode* first;
	ListNode* last;

	List();
	~List();

	Section* newSection();
	Tuple<ListNode*, int> getSection(int index);
	bool removeSection(int index);

	int countSelectorOccurrences(const String& selectorName);
	int countAttributeOccurrences(const String& attributeName);

	Section* operator[](int index);

};

#endif