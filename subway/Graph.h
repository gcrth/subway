#pragma once
#include"pch.h"
#include"SubwayLine.h"
#include"Station.h"

class Graph
{
public:
	Graph(vector<string>describes);
	virtual ~Graph();
	vector<SubwayLine>subwayLine;
	vector<Station>stations;
private:

};

