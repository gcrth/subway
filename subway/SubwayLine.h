#pragma once
#include"pch.h"
#include"Station.h"
using namespace std;

class SubwayLine
{
public:
	string name;
	vector<Station *>stationsPointer;

	SubwayLine();
	SubwayLine(const char * name_);
	virtual ~SubwayLine();

};

