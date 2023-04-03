#include "Attribute.h"

Attribute::Attribute()
{

}

Attribute::Attribute(const String& name, const String& value) :
	name{name}, value{value}
{

}

Attribute::Attribute(String&& name, String&& value) :
	name{ static_cast<String&&>(name) }, value{ static_cast<String&&>(value) }
{

}

Attribute& Attribute::operator=(const Attribute& attribute)
{
	this->name = attribute.name;
	this->value = attribute.name;
	return *this;
}

Attribute& Attribute::operator=(Attribute&& attribute) noexcept
{
	this->name = static_cast<String&&>(attribute.name);
	this->value = static_cast<String&&>(attribute.value);
	return *this;
}

bool operator==(const Attribute& lhs, const Attribute& rhs)
{
	if (lhs.name == rhs.name)
		return true;

	return false;
}

bool operator==(const Attribute& lhs, int length)
{
	if (lhs.name.getLength() + lhs.value.getLength() != length)
		return false;
	
	return true;
}

std::ostream& operator<<(std::ostream& os, const Attribute& attribute)
{
	os << attribute.name << " " << attribute.value;
	return os;
}
