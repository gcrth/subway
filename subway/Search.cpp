#include "pch.h"
#include "Search.h"



Search::~Search()
{
}

Search::Search(wstring from_, wstring to_, Graph &graph_,int costOfTransform_) :graph(graph_)
{
	costOfTransform = costOfTransform_;
	fromString = from_;
	toString = to_;
	from = -1;
	to = -1;
	for (int i = 0; i < graph.stations.size(); i++)
	{
		if (graph.stations[i].isEqual(fromString.c_str()))
		{
			from = i;
			if (to != -1)break;
		}
		else if (graph.stations[i].isEqual(toString.c_str()))
		{
			to = i;
			if (from != -1)break;
		}
	}
	if (from == -1 || to == -1)throw invalid_argument("no_such_city");

}

Search::Search(wstring from_, Graph &graph_,int costOfTransform_) :graph(graph_)
{
	costOfTransform = costOfTransform_;
	fromString = from_;
	from = -1;
	for (int i = 0; i < graph.stations.size(); i++)
	{
		if (graph.stations[i].isEqual(fromString.c_str()))
		{
			from = i;
			break;
		}
	}
	if (from == -1)throw invalid_argument("no_such_city");
}

Route Search::SearchThePath()
{
	for (int i = 0; i < graph.stations[from].subwayLinePointer.size(); i++)
	{
		route.emplace(graph.stations[from].subwayLinePointer[i], from);
	}
	while (true)
	{
		Route x(route.top());
		route.pop();
		if (isArrived(x))
		{
			return x;
		}
		for (int i = 0; i < graph.stations[x.location].linkBetweenStation.size(); i++)
		{
			bool isOnThisLine = false;
			for (int j = 0; j < graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].subwayLinePointer.size(); j++)
			{
				if (graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].subwayLinePointer[j] == x.theLineNowTake)
				{
					isOnThisLine = true;
					break;
				}
			}
			if (!isOnThisLine)continue;
			int station = graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].secondStation;
			bool isVisited = false;
			for (int j = 0; j < x.reachedStations.size(); j++)
			{
				if (x.reachedStations[j] == station)
				{
					isVisited = true;
					break;
				}
			}
			if (!isVisited)
			{
				Route y(x);
				y.reachedStations.push_back(station);
				y.location = station;
				y.steps.emplace_back(stepType::nextStaiton, station);
				route.push(y);
				for (int k = 0; k < graph.stations[station].subwayLinePointer.size(); k++)
				{
					if (graph.stations[station].subwayLinePointer[k] == x.theLineNowTake)continue;
					y.steps.emplace_back(stepType::transform, graph.stations[station].subwayLinePointer[k]);
					y.theLineNowTake = graph.stations[station].subwayLinePointer[k];
					route.push(y);
					y.steps.pop_back();
				}
			}
		}
	}

}

Route Search::SearchTheTraversal()
{
	for (int i = 0; i < graph.stations[from].subwayLinePointer.size(); i++)
	{
		route.emplace(graph.stations[from].subwayLinePointer[i], from);
	}
	while (true)
	{
		Route x(route.top());
		route.pop();
		if (isAllReached(x))
		{
			return x;
		}
		for (int i = 0; i < graph.stations[x.location].linkBetweenStation.size(); i++)
		{
			bool isOnThisLine = false;
			for (int j = 0; j < graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].subwayLinePointer.size(); j++)
			{
				if (graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].subwayLinePointer[j] == x.theLineNowTake)
				{
					isOnThisLine = true;
				}
			}
			if (!isOnThisLine)continue;
			int station = graph.linkBetweenStation[graph.stations[x.location].linkBetweenStation[i]].secondStation;
			Route y(x);
			y.cost;
			y.location = station;
			y.steps.emplace_back(stepType::nextStaiton, station);
			route.push(y);
			y.cost += costOfTransform;
			for (int k = 0; k < graph.stations[station].subwayLinePointer.size(); k++)
			{
				if (graph.stations[station].subwayLinePointer[k] == x.theLineNowTake)continue;
				y.steps.emplace_back(stepType::transform, graph.stations[station].subwayLinePointer[k]);
				y.theLineNowTake = graph.stations[station].subwayLinePointer[k];
				route.push(y);
				y.steps.pop_back();
			}
		}
	}
}

bool Search::isArrived(Route x)
{
	for (int i = 0; i < x.reachedStations.size(); i++)
	{
		if (x.reachedStations[i] == to)return true;
	}
	return false;
}

bool Search::isAllReached(Route x)
{
	if (x.reachedStations.size() == graph.stations.size())return true;
	return false;
}

wstring Search::findThePath()
{
	result = SearchThePath();
	return outPut();
}

wstring Search::findTheTraversal()
{
	result = SearchTheTraversal();
	return outPut();
}

wstring Search::outPut()
{
	wstring resultString;
	for (int i = 0; i < result.steps.size(); i++)
	{
		if (result.steps[i].type == stepType::transform)
		{
			if(i!=0)resultString += L"»»³Ë ";
			else resultString += L"³Ë×ø ";
			resultString += graph.subwayLine[result.steps[i].action].name;
		}
		else
		{
			resultString += graph.stations[result.steps[i].action].name;
		}
		resultString += L"\n";
	}
	return resultString;
}

wstring Search::findTheTraversalSimple()
{
	result = SearchTheTraversal();
	return simpleOutPut();
}

wstring Search::simpleOutPut()
{
	wstring resultString;
	for (int i = 0; i < result.steps.size(); i++)
	{
		if (result.steps[i].type == stepType::transform)
		{
			
		}
		else
		{
			resultString += graph.stations[result.steps[i].action].name;
		}
		resultString += L"\n";
	}
	return resultString;
}