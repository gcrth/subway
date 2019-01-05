#include "pch.h"
#include "Graph.h"

Graph::Graph(vector<wstring>describes)
{
	for (int i = 0; i < describes.size(); i++)
	{
		dealOneDescribe(describes[i]);
	}
}

Graph::Graph(){}

int Graph::dealOneDescribe(wstring describe)
{
	wchar_t * tokenPointer;
	vector<wstring>token;
	wchar_t * describeStr = new wchar_t[describe.size()+1];
	wcscpy(describeStr, describe.c_str());
	bool onWay(false);

	tokenPointer = wcstok(describeStr, L"\t");
	subwayLine.push_back(SubwayLine(tokenPointer));
	if (subwayLine.back().name.back() == '*')
	{
		onWay = true;
		subwayLine.back().name.pop_back();
	}
	tokenPointer = wcstok(NULL, L"\t");

	while (tokenPointer)
	{
		token.push_back(wstring(tokenPointer));
		tokenPointer = wcstok(NULL, L"\t");
	}

	int lastStation;
	int thisStation;

	for (int i = 0; i < token.size() - 1; i++)
	{
		bool isExist(false);
		int stationNo(0);

		for (int j = 0; j < stations.size(); j++)
		{
			if (stations[j].isEqual(token[i].c_str()))
			{
				isExist = true;
				stationNo = j;
				break;
			}
		}
		if (isExist)
		{
			subwayLine.back().stationsPointer.push_back(stationNo);
			stations[stationNo].subwayLinePointer.push_back(subwayLine.size() - 1);
			thisStation = stationNo;
		}
		else
		{
			stations.push_back(Station(token[i].c_str()));
			subwayLine.back().stationsPointer.push_back(stations.size() - 1);
			stations.back().subwayLinePointer.push_back(subwayLine.size() - 1);
			thisStation = stations.size() - 1;
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
				linkBetweenStation[linkNo].subwayLinePointer.push_back(subwayLine.size() - 1);
				stations[lastStation].linkBetweenStation.push_back(linkNo);
			}
			else
			{
				linkBetweenStation.push_back(LinkBetweenStation(lastStation, thisStation, subwayLine.size() - 1));
				stations[lastStation].linkBetweenStation.push_back(linkBetweenStation.size()-1);
			}
			if (!onWay)
			{
				for (int j = 0; j < linkBetweenStation.size(); j++)
				{
					if (linkBetweenStation[j].isEqual(thisStation, lastStation))
					{
						isExist = true;
						linkNo = j;
						break;
					}
				}
				if (isExist)
				{
					linkBetweenStation[linkNo].subwayLinePointer.push_back(subwayLine.size() - 1);
					stations[thisStation].linkBetweenStation.push_back(linkNo);
				}
				else
				{
					linkBetweenStation.push_back(LinkBetweenStation(thisStation,lastStation, subwayLine.size() - 1));
					stations[thisStation].linkBetweenStation.push_back(linkBetweenStation.size() - 1);
				}
			}
		}
		lastStation = thisStation;
	}

	//»·Ïß
	if (token.back() == L"1")
	{
		bool isExist = false;
		int linkNo(0);
		thisStation = subwayLine.back().stationsPointer.front();
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
			linkBetweenStation[linkNo].subwayLinePointer.push_back(subwayLine.size() - 1);
			stations[lastStation].linkBetweenStation.push_back(linkNo);
		}
		else
		{
			linkBetweenStation.push_back(LinkBetweenStation(lastStation, thisStation, subwayLine.size() - 1));
			stations[lastStation].linkBetweenStation.push_back(linkBetweenStation.size() - 1);
		}
		for (int j = 0; j < linkBetweenStation.size(); j++)
		{
			if (linkBetweenStation[j].isEqual(thisStation, lastStation))
			{
				isExist = true;
				linkNo = j;
				break;
			}
		}
		if (isExist)
		{
			linkBetweenStation[linkNo].subwayLinePointer.push_back(subwayLine.size() - 1);
			stations[thisStation].linkBetweenStation.push_back(linkNo);
		}
		else
		{
			linkBetweenStation.push_back(LinkBetweenStation(thisStation, lastStation, subwayLine.size() - 1));
			stations[thisStation].linkBetweenStation.push_back(linkBetweenStation.size() - 1);
		}
	}

	delete [] describeStr;
	return 0;
}


Graph::~Graph()
{
}
