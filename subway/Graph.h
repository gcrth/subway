#pragma once
#include"pch.h"
#include"SubwayLine.h"
#include"Station.h"
#include"LinkBetweenStation.h"

class Graph
{
public:
	vector<SubwayLine>subwayLine;
	vector<Station>stations;
	vector<LinkBetweenStation>linkBetweenStation;

	Graph(vector<string>describes);
	virtual ~Graph();
private:
	int dealOneDescribe(string describe);
};

