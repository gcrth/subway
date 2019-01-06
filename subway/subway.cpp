#include "pch.h"
#include <iostream>
#include"init.h"
#include"Utility.h"

int getArg(int argc, char* argv[])
{
	if (argc < 4)throw invalid_argument("wrong_number");
	vector<wstring>arg;
	wchar_t wargv[10000];
	for (int i = 0; i < argc; i++)
	{
		mbstowcs(wargv, argv[i], 10000);
		arg.push_back(wstring(wargv));
	}
	Graph graph;
	if (arg[1]==L"/shanghai")
	{
		graph = init(City::shanghai);
	}
	else if(arg[1]==L"/beijing")
	{
		graph = init(City::beijing);
	}
	else
	{
		throw invalid_argument("invalid_city");
	}
	if(arg[2][0]!='/'||arg[2].size()!=2)throw invalid_argument("invalid_argument");
	switch (arg[2][1])
	{
	case 'a':
	{

		break;
	}
	case 'b':
	{
		wstring from;
		wstring to;

		break;
	}
	case 'c':
	{
		if(arg.size()!=4)throw invalid_argument("invalid_argument");
		int subwayNo(-1);
		for (int i = 0; i < graph.subwayLine.size(); i++)
		{
			if (graph.subwayLine[i].name == arg[3])
			{
				subwayNo = i;
			}
		}
		if(subwayNo==-1)throw invalid_argument("invalid_subway");
		for (int i = 0; i < graph.subwayLine[subwayNo].stationsPointer.size(); i++)
		{
			wcout << graph.stations[graph.subwayLine[subwayNo].stationsPointer[i]].name << endl;
		}
		break;
	}
	case 'g':
	{

		break;
	}
	case 'z':
	{

		break;
	}
	default:
	{
		throw invalid_argument("no_this_job");
	}
	}
	return 0;
}

int appmain(int argc, char* argv[])
{
	try
	{
		getArg(argc, argv);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	appmain(argc,argv);
	return 0;
}

