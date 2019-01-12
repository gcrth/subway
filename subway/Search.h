#pragma once
#include"pch.h"
#include"Graph.h"

enum stepType
{
	transform,
	nextStaiton
};

struct Step
{
	stepType type;
	int action;
	Step(stepType type_,int action_)
	{
		type = type_;
		 action = action_;
	}
};

struct Route
{
	vector<Step>steps;
	int cost;
	vector<int>reachedStations;
	int location;
	int theLineNowTake;
	Route(int subWayLine,int from)
	{
		steps.emplace_back(stepType::transform,subWayLine);
		location = from;
		theLineNowTake = subWayLine;
		reachedStations.push_back(from);
		cost = 0;
	}
	Route()
	{

	}
};

class Compare
{
public:
	bool operator()(Route left, Route right) const
	{
		return left.cost > right.cost;
	}
};

class Compare_a
{
public:
	bool operator()(Route left, Route right) const
	{
		return ((left.cost +right.reachedStations.size() )>(right.cost+ left.reachedStations.size() ));
	}
};

class Search
{
public:
	Search(wstring from_, wstring to_, Graph& graph_,int costOfTransform_);
	Search(wstring from_, Graph& graph_,int costOfTransform_);
	Route SearchThePath();
	Route SearchTheTraversal();
	virtual ~Search();
	wstring findThePath();
	wstring findTheTraversal();
	wstring findTheTraversalForGUI();
	wstring findThePathForGUI();

	wstring fromString;
	wstring toString;
	int from;
	int to;
	Graph& graph;
	int costOfTransform=0;
	Route result;
	priority_queue<Route, vector<Route>, Compare> route;
	priority_queue<Route, vector<Route>, Compare_a> route_a;

private:
	bool isArrived(Route x);
	bool isAllReached(Route x);
	wstring outPut();
	wstring outPutForGUI();
	Route findTheShortestUntouchedPoint(Route route);
};

