#pragma once
#include"pch.h"
#include"Station.h"
#include"SubwayLine.h"
using namespace std;

class LinkBetweenStation
{
public:
	Station*firstStation;
	Station*secondStation;
	vector<SubwayLine*>subwayLinePointer;

	LinkBetweenStation();
	LinkBetweenStation(Station*firstStation_, Station*secondStation_,SubwayLine*subwayLinePointer_);
	virtual ~LinkBetweenStation();
	bool isEqual(Station*firstStation_, Station*secondStation_);
};

