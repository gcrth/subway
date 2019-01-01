#include "pch.h"
#include "Station.h"


Station::Station()
{
}

Station::Station(const char* name_)
{
	name = name_;
}

Station::~Station()
{
}

bool Station::isEqual(const char *name_)
{
	return strcmp(name.c_str(), name_) == 0;
}
