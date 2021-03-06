#include "pch.h"
#include "Search.h"



Search::~Search()
{
}

Search::Search(wstring from_, wstring to_, Graph &graph_, int costOfTransform_) :graph(graph_)
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
		if (graph.stations[i].isEqual(toString.c_str()))
		{
			to = i;
			if (from != -1)break;
		}
	}
	if (from == -1 || to == -1)throw invalid_argument("no_such_station");

}

Search::Search(wstring from_, Graph &graph_, int costOfTransform_) :graph(graph_)
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
	if (from == -1)throw invalid_argument("no_such_station");
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
				y.cost++;
				y.reachedStations.push_back(station);
				y.location = station;
				y.steps.emplace_back(stepType::nextStaiton, station);
				route.push(Route(y));
				y.cost += costOfTransform;
				for (int k = 0; k < graph.stations[station].subwayLinePointer.size(); k++)
				{
					if (graph.stations[station].subwayLinePointer[k] == x.theLineNowTake)continue;
					y.steps.emplace_back(stepType::transform, graph.stations[station].subwayLinePointer[k]);
					y.theLineNowTake = graph.stations[station].subwayLinePointer[k];
					route.push(Route(y));
					y.steps.pop_back();
				}
			}
		}
	}

}

Route Search::findTheShortestUntouchedPoint(Route route)
{
	priority_queue<Route, vector<Route>, Compare> routeSet;
	for (int i = 0; i < graph.stations[route.location].subwayLinePointer.size(); i++)
	{
		if (route.theLineNowTake == graph.stations[route.location].subwayLinePointer[i])
		{
			Route x(route);
			x.reachedStations.clear();
			x.reachedStations.push_back(x.location);
			routeSet.push(x);
		}
		else
		{
			Route x(route);
			x.steps.emplace_back(stepType::transform, graph.stations[route.location].subwayLinePointer[i]);
			x.cost += costOfTransform;
			x.theLineNowTake = graph.stations[route.location].subwayLinePointer[i];
			x.reachedStations.clear();
			x.reachedStations.push_back(x.location);
			routeSet.push(x);
		}
	}
	while (true)
	{
		Route x(routeSet.top());
		routeSet.pop();
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
			for (int j = 0; j < route.reachedStations.size(); j++)
			{
				if (route.reachedStations[j] == station)
				{
					isVisited = true;
					break;
				}
			}
			if (!isVisited)
			{
				Route y(x);
				y.cost++;
				y.reachedStations.push_back(station);
				y.location = station;
				y.steps.emplace_back(stepType::nextStaiton, station);
				
				for (int k = 0; k < route.reachedStations.size(); k++)
				{
					y.reachedStations.push_back(route.reachedStations[k]);
				}
				sort(y.reachedStations.begin(), y.reachedStations.end());
				vector<int>::iterator new_end;
				new_end = std::unique(y.reachedStations.begin(), y.reachedStations.end());
				y.reachedStations.erase(new_end, y.reachedStations.end());
				return y;
			}
			else
			{
				isVisited = false;
				for (int j = 0; j < x.reachedStations.size(); j++)
				{
					if (x.reachedStations[j] == station)
					{
						isVisited = true;
						break;
					}
				}
				if (isVisited)continue;
				Route y(x);
				y.cost++;
				y.location = station;
				y.steps.emplace_back(stepType::nextStaiton, station);
				y.reachedStations.push_back(station);
				routeSet.push(Route(y));
				y.cost += costOfTransform;
				for (int k = 0; k < graph.stations[station].subwayLinePointer.size(); k++)
				{
					if (graph.stations[station].subwayLinePointer[k] == x.theLineNowTake)continue;
					y.steps.emplace_back(stepType::transform, graph.stations[station].subwayLinePointer[k]);
					y.theLineNowTake = graph.stations[station].subwayLinePointer[k];
					routeSet.push(Route(y));
					y.steps.pop_back();
				}
			}
		}
	}
}

Route Search::SearchTheTraversal()
{
	Route xbest;
	int cost = 0xffffff;
	for (int k = 0; k < graph.stations[from].subwayLinePointer.size(); k++)
	{
		Route x(graph.stations[from].subwayLinePointer[k], from);
		while (!isAllReached(x))
		{
			x = findTheShortestUntouchedPoint(x);
		}
		x.reachedStations.erase(x.reachedStations.begin() + from);
		x = findTheShortestUntouchedPoint(x);
		if (x.cost < cost)xbest=x;
	}
	return xbest;
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
	if (x.reachedStations.size() == graph.stations.size())
	{
		return true;
	}
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
	wchar_t cost[10000];
	_itow(result.cost, cost, 10);
	resultString += wstring(cost);
	resultString += L"\n";
	resultString += graph.stations[from].name;
	resultString += L"\n";
	for (int i = 0; i < result.steps.size(); i++)
	{
		if (result.steps[i].type == stepType::transform)
		{
			resultString += L"���� ";
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

wstring Search::findTheTraversalForGUI()
{
	result = SearchTheTraversal();
	return outPutForGUI();
}

wstring Search::findThePathForGUI()
{
	result = SearchThePath();
	return outPutForGUI();
}

wstring Search::outPutForGUI()
{
	wstring resultString;

	resultString += graph.stations[from].name;
	resultString += L"\n";
	for (int i = 0; i < result.steps.size(); i++)
	{
		if (result.steps[i].type == stepType::transform)
		{
			continue;
		}
		else
		{
			resultString += graph.stations[result.steps[i].action].name;
		}
		resultString += L"\n";
	}
	return resultString;
}