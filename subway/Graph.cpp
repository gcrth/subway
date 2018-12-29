#include "pch.h"
#include "Graph.h"


Graph::Graph(vector<string>describes)
{
	for (int i = 0; i < describes.size(); i++)
	{
		subwayLine.push_back(SubwayLine(describes[i],stations,i));
	}
}


Graph::~Graph()
{
}
