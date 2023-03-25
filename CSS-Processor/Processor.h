#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "String.h"
using string = String;

class Processor
{
private:
	//VARIABLES
	string prevAttributeName;
	int numberOfSections;

	//FLAGS
	bool readMode; //false - CSS, true - Commands
	bool wasPreviousElementAttributeName;
	bool isInSection;
	bool isInBlock;

	//CSS FUNCTIONS
	void readCSS();
	void interpretCSS(char* text, int length);
	void checkAttribute(char* text, int length);
	
	//COMMAND FUNCTIONS

public:
	Processor();
	~Processor();

	void start();
	void stop();
};

#endif