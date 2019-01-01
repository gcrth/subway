#include "pch.h"
#include "LinkBetweenStation.h"


LinkBetweenStation::LinkBetweenStation()
{
}

LinkBetweenStation::LinkBetweenStation(Station*firstStation_, Station*secondStation_, SubwayLine*subwayLinePointer_)
{
	firstStation = firstStation_;
	secondStation = secondStation_;
	subwayLinePointer.push_back(subwayLinePointer_);
}


LinkBetweenStation::~LinkBetweenStation()
{
}

bool LinkBetweenStation::isEqual(Station*firstStation_, Station*secondStation_)
{
	return ((((firstStation) == firstStation_) &&
		((secondStation) == secondStation_)) ||
		(((firstStation) == secondStation_) &&
		((secondStation) == firstStation_)));
}
