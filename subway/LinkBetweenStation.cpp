#include "pch.h"
#include "LinkBetweenStation.h"


LinkBetweenStation::LinkBetweenStation()
{
}

LinkBetweenStation::LinkBetweenStation(int firstStation_, int secondStation_, int subwayLinePointer_)
{
	firstStation = firstStation_;
	secondStation = secondStation_;
	subwayLinePointer.push_back(subwayLinePointer_);
}


LinkBetweenStation::~LinkBetweenStation()
{
}

bool LinkBetweenStation::isEqual(int firstStation_, int secondStation_)
{
	return ((((firstStation) == firstStation_) &&
		((secondStation) == secondStation_)) );
	/*||
		(((firstStation) == secondStation_) &&
		((secondStation) == firstStation_))*/
}
