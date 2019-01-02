#include"pch.h"
#include"init.h"
#include"Graph.h"
#include "Utility.h"
#include "IO.h"
using namespace std;


Graph makeGraph(const char* fileName)
{
	InFile inFile(fileName);
	if (!inFile.open())throw runtime_error("unable_to_open_file");
	char inBuf[1000];
	vector<string>describes;
	for (int i = 0;; i++)
	{
		if (inFile.gets(inBuf, sizeof(inBuf)) == NULL)break;
		describes.push_back(string(inBuf));
	}
	return Graph(describes);
}

Graph init(int city)
{
	switch (city)
	{
	case City::beijing:
	{
		return makeGraph("beijing_subway.txt");
		break;
	}
	case City::shanghai:
	{
		throw runtime_error("no_this_city");
		break;
	}
	default:
		throw runtime_error("no_this_city");
		break;
	}
}


