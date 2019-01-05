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

	Graph(vector<wstring>describes);
	Graph();
	virtual ~Graph();
private:
	int dealOneDescribe(wstring describe);
};

