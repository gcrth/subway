#include "pch.h"
#include "Graph.h"

Graph::Graph(vector<string>describes)
{
	for (int i = 0; i < describes.size(); i++)
	{
		dealOneDescribe(describes[i]);
	}
}

int Graph::dealOneDescribe(string describe)
{
	char * tokenPointer;
	vector<string>token;
	char * describeStr = new char[describe.size()];
	strcpy(describeStr, describe.c_str());
	
	tokenPointer = strtok(describeStr, "\t");
	subwayLine.push_back(SubwayLine(tokenPointer));
	tokenPointer = strtok(NULL, "\t");

	while (tokenPointer)
	{
		token.push_back(string(tokenPointer));
		tokenPointer = strtok(NULL, "\t");
	}

	Station* lastStation;
	Station* thisStation;

	for (int i = 0; i < token.size() - 1; i++)
	{
		bool isExist(false);
		int stationNo(0);

		for (int j = 0; j < stations.size(); j++)
		{
			if (stations[j].isEqual(token[j].c_str()))
			{
				isExist = true;
				stationNo = j;
				break;
			}
		}
		if (isExist)
		{
			subwayLine.back().stationsPointer.push_back(&(stations[stationNo]));
			stations[stationNo].subwayLinePointer.push_back(&(subwayLine.back()));
			thisStation = &(stations[stationNo]);
		}
		else
		{
			stations.push_back(Station(token[i].c_str()));
			subwayLine.back().stationsPointer.push_back(&(stations.back()));
			stations.back().subwayLinePointer.push_back(&(subwayLine.back()));
			thisStation = &(stations.back());
		}

		isExist = false;
		int linkNo(0);
		if (i != 0)
		{
			for (int j = 0; j < linkBetweenStation.size(); j++)
			{
				if (linkBetweenStation[j].isEqual(lastStation, thisStation))
				{
					isExist = true;
					linkNo = j;
					break;
				}
			}
			if (isExist)
			{
				linkBetweenStation[linkNo].subwayLinePointer.push_back(&(subwayLine.back()));
			}
			else
			{
				linkBetweenStation.push_back(LinkBetweenStation(lastStation, thisStation, &(subwayLine.back())));
			}
		}
		lastStation = thisStation;
	}
	delete[] describeStr;
	return 0;
}


Graph::~Graph()
{
}
