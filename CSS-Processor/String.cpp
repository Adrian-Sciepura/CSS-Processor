#include "String.h"

String::String()
{
	this->cstring = new char[1];
	this->cstring[0] = '\0';
	this->length = 0;
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

String& String::operator=(const String& source)
{
	delete[] this->cstring;
	this->cstring = new char[source.length + 1];
	strcpy(this->cstring, source.cstring);
	this->length = source.length;
	return *this;
}

String& String::operator=(String&& source) noexcept
{
	delete[] this->cstring;
	this->cstring = source.cstring;
	this->length = source.length;
	source.cstring = nullptr;
	source.length = 0;
	return *this;
}

const char& String::operator[](int index) const
{
	return cstring[index];
}

String operator+(const String& lhs, const String& rhs)
{
	int length = lhs.length + rhs.length + 1;
	char* tmp = new char[length];
	strcpy(tmp, lhs.cstring);
	strcat(tmp, rhs.cstring);
	String s = tmp;
	delete[] tmp;
	return s;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.length != rhs.length)
		return false;

	for (int i = 0; i < lhs.length; i++)
		if (lhs.cstring[i] != rhs.cstring[i])
			return false;

	return true;
}

bool operator==(const String& lhs, int length)
{
	if (lhs.length != length)
		return false;

	return true;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	os << string.cstring;
	return os;
}