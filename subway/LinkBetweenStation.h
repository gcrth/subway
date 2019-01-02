#pragma once
#include"pch.h"
#include"Station.h"
#include"SubwayLine.h"

class LinkBetweenStation
{
public:
	int firstStation;
	int secondStation;
	vector<int>subwayLinePointer;

	LinkBetweenStation();
	LinkBetweenStation(int firstStation_, int secondStation_,int subwayLinePointer_);
	virtual ~LinkBetweenStation();
	bool isEqual(int firstStation_, int secondStation_);
};

