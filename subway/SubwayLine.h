#pragma once
#include"pch.h"
#include"Station.h"

class SubwayLine
{
public:
	wstring name;
	vector<int>stationsPointer;

	SubwayLine();
	SubwayLine(const wchar_t * name_);
	virtual ~SubwayLine();

};

