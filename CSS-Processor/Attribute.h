#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "String.h"
#include <iostream>

class Attribute
{
public:
	String name;
	String value;

	Attribute();
	Attribute(const String& name, const String& value);
	Attribute(String&& name, String&& value);

	Attribute& operator=(const Attribute& attribute);
	Attribute& operator=(Attribute&& attribute) noexcept;
	friend bool operator==(const Attribute& lhs, const Attribute& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Attribute& attribute);
};

#endif