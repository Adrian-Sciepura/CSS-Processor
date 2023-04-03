#ifndef PROCESSOR_H
#define PROCESSOR_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include "String.h"
#include "List.h"

class Processor
{
private:
	//VARIABLES
	List list;
	Section* lastSection;
	String prevAttributeName;

	//FLAGS
	bool readMode; //false - CSS, true - Commands
	bool wasPreviousElementAttributeName;
	bool gotAllSelectors;
	bool isInSection;
	bool foundBracket;
	bool foundColon;

	//FUNCTIONS
	bool checkExtra(const char* text);
	void printResult(char* arg1, char& action, char* arg2);

	//CSS FUNCTIONS
	void interpretCSS(char* text, int length);
	
	//COMMAND FUNCTIONS
	void interpretCommand(char* text);

public:
	Processor();
	~Processor();

	void start();
};

#endif