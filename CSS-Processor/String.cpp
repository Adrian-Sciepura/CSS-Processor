#include "String.h"

String::String()
{
	this->cstring = new char[1];
	this->cstring[0] = '\0';
	this->length = 1;
}

String::String(const char* source)
{
	int sourceLength = strlen(source);
	this->cstring = new char[sourceLength + 1];
	strcpy(this->cstring, source);
	this->length = sourceLength;
}

String::String(const String& source) :
	String(source.cstring)
{
	
}

String::String(String&& source) noexcept
{
	this->cstring = source.cstring;
	this->length = source.length;
	source.cstring = nullptr;
	source.length = 0;
}

String::~String()
{
	delete[] this->cstring;
}

int String::getLength() const
{
	return this->length;
}

String& String::operator=(const char* source)
{
	delete[] this->cstring;
	int sourceLength = strlen(source);
	this->cstring = new char[sourceLength + 1];
	strcpy(this->cstring, source);
	this->length = sourceLength;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	os << string.cstring;
	return os;
}