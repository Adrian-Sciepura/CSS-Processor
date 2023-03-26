#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "String.h"
#include "List.h"
using string = String;

class Processor
{
private:
	//VARIABLES
	List list;
	string prevAttributeName;

	//FLAGS
	bool readMode; //false - CSS, true - Commands
	bool wasPreviousElementAttributeName;
	bool isInSection;
	bool isInBlock;

	//FUNCTIONS
	bool checkExtra(const char* text, int length);

	//CSS FUNCTIONS
	void interpretCSS(char* text, int length);
	void checkAttribute(char* text, int length);
	
	//COMMAND FUNCTIONS
	void interpretCommand(char* text, int length);

public:
	Processor();
	~Processor();

	void start();
};

#endif