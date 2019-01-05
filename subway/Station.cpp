#include "pch.h"
#include "Station.h"


Station::Station()
{
}

Station::Station(const wchar_t* name_)
{
	name = name_;
}

Station::~Station()
{
}

bool Station::isEqual(const wchar_t *name_)
{
	return name == wstring(name_);
}
