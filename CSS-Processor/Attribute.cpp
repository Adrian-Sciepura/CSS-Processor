#include "Attribute.h"

Attribute::Attribute()
{

}

Attribute::Attribute(const String& name, const String& value)
{
	this->name = name;
	this->value = value;
}

Attribute::Attribute(String&& name, String&& value)
{
	this->name = static_cast<String&&>(name);
	this->value = static_cast<String&&>(value);
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
