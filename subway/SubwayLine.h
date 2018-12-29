#pragma once
#include"pch.h"
#include"Station.h"

class SubwayLine
{
public:
	SubwayLine();
	SubwayLine(string describe, vector<Station> &stations_,int Id);
	int subwayLineId;
	string name;
	vector<Station *>stations;
	virtual ~SubwayLine();
};

