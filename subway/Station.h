#pragma once
#include"pch.h"
#include"SubwayLine.h"

class Station
{
public:
	string name;
	vector <int> subwayLinePointer;

	Station();
	Station(const char * name_);
	virtual ~Station();
	bool isEqual(const char *name_);
	
};

