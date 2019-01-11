#include "pch.h"
#include <iostream>
#include"init.h"
#include"Utility.h"
#include"Search.h"

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
		if (argc != 4 && argc != 5)throw invalid_argument("wrong_number");
		wstring from;
		from = arg[3];
		int costOfTransform = 0;
		if (argc == 5)
		{
			if (arg[4] == L"/adv")costOfTransform = 3;
			else throw invalid_argument("invalid_argument");
		}
		wstring result=Search(from, graph, costOfTransform).findTheTraversal();
		wcout << result;
		break;
	}
	case 'b':
	{
		if (argc != 5 && argc != 6)throw invalid_argument("wrong_number");
		wstring from;
		wstring to;
		from = arg[3];
		to = arg[4];
		int costOfTransform = 0;
		if (argc == 6)
		{
			if (arg[5] == L"/adv")costOfTransform = 3;
			else throw invalid_argument("invalid_argument");
		}
		wstring result = Search(from,to, graph, costOfTransform).findThePath();
		wcout << result ;
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
		if (argc != 4 && argc != 5)throw invalid_argument("wrong_number");
		wstring from;
		from = arg[3];
		int costOfTransform = 0;
		if (argc == 5)
		{
			if (arg[4] == L"/adv")costOfTransform = 3;
			else throw invalid_argument("invalid_argument");
		}
		wstring result = Search(from, graph, costOfTransform).findTheTraversal();
		wcout << result;
		OutFile outfile("result.txt");
		if (!outfile.open())throw runtime_error("unable_to_open_file");
		if(outfile.puts(result.c_str())<0)throw runtime_error("unable_to_output_file");
		outfile.close();
		//call the python
		system("python gui.py");
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
	//zh-CN
	setlocale(LC_ALL, "zh-CN");
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

