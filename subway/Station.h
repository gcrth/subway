#pragma once
#include"pch.h"
#include"SubwayLine.h"

class Station
{
public:
	wstring name;
	vector <int> subwayLinePointer;
	vector<int>linkBetweenStation;
	Station();
	Station(const wchar_t * name_);
	virtual ~Station();
	bool isEqual(const wchar_t *name_);
	
};

