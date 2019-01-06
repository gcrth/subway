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
	string name;
};

struct Route
{
	vector<Step>steps;
	int cost;

};

class Compare
{
public:
	bool operator()(Route left, Route right) const
	{
		return left.cost > left.cost;
	}
};

class Search
{
public:
	Search();
	Search(wstring from_, wstring to_);
	Search(wstring from_);
	int SearchThePath();
	int SearchTheTraversal();
	virtual ~Search();

	wstring from;
	wstring to;
	
	priority_queue<Route, vector<Route>, Compare> route;
};

