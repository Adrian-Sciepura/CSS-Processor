#ifndef SECTION_H
#define SECTION_H

#include "ForwardList.h"
#include "String.h"
#include "Attribute.h"

class Section
{
public:
	ForwardList<String> selectors;
	ForwardList<Attribute> attributes;
	void print();
};

#endif