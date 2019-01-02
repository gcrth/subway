#pragma once
#include"pch.h"
#include"Station.h"

class SubwayLine
{
public:
	string name;
	vector<int>stationsPointer;

	SubwayLine();
	SubwayLine(const char * name_);
	virtual ~SubwayLine();

};

