#ifndef STRING_H
#define STRING_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>

class String
{
private:
	char* cstring;
	int length;

public:
	String();
	String(const char* source);
	String(const String& source);
	String(String&& source) noexcept;
	~String();

	int getLength() const;

	String& operator=(const char* source);
	friend std::ostream& operator<<(std::ostream& os, const String& string);
};

#endif