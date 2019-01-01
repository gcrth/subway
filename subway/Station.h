#pragma once
#include"pch.h"
#include"SubwayLine.h"
using namespace std;

class Station
{
public:
	string name;
	vector <SubwayLine *> subwayLinePointer;

	Station();
	Station(const char * name_);
	virtual ~Station();
	bool isEqual(const char *name_);
	
};

