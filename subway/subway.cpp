#include "pch.h"
#include <iostream>
#include"init.h"
#include"Utility.h"
#include"Search.h"

int getArg(int argc, char* argv[])
{
	if (argc < 3)throw invalid_argument("wrong_number");
	vector<wstring>arg;
	wchar_t wargv[10000];
	for (int i = 0; i < argc; i++)
	{
		mbstowcs(wargv, argv[i], 10000);
		arg.push_back(wstring(wargv));
	}
	Graph graph;
	int city;
	if (arg[1] == L"/shanghai")
	{
		graph = init(City::shanghai);
		city = City::shanghai;
	}
	else if (arg[1] == L"/beijing")
	{
		graph = init(City::beijing);
		city = City::beijing;
	}
	else if (arg[1] == L"/small_beijing")
	{
		graph = init(City::small_beijing);
		city = City::small_beijing;
	}
	else
	{
		throw invalid_argument("invalid_city");
	}
	if (arg[2][0] != '/' || arg[2].size() != 2)throw invalid_argument("invalid_argument");
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
		wstring result = Search(from, graph, costOfTransform).findTheTraversal();
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
		wstring result = Search(from, to, graph, costOfTransform).findThePath();
		wcout << result;
		break;
	}
	case 'c':
	{
		if (arg.size() != 4)throw invalid_argument("invalid_argument");
		int subwayNo(-1);
		for (int i = 0; i < graph.subwayLine.size(); i++)
		{
			if (graph.subwayLine[i].name == arg[3])
			{
				subwayNo = i;
			}
		}
		if (subwayNo == -1)throw invalid_argument("invalid_subway");
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
		wstring result = Search(from, graph, costOfTransform).findTheTraversalForGUI();
		wcout << result;
		OutFile outfile("result.txt");
		if (!outfile.open())throw runtime_error("unable_to_open_file");
		if (outfile.puts(result.c_str()) < 0)throw runtime_error("unable_to_output_file");
		outfile.close();
		//call the python
		system("python gui.py");
		break;
	}
	case 'k':
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
		wstring result = Search(from, to, graph, costOfTransform).findThePathForGUI();
		wcout << result;
		OutFile outfile("result.txt");
		if (!outfile.open())throw runtime_error("unable_to_open_file");
		if (outfile.puts(result.c_str()) < 0)throw runtime_error("unable_to_output_file");
		outfile.close();
		//call the python
		system("python gui.py");
		break;
	}
	case 'p':
	{
		vector<vector<int> >des;
		des.resize(graph.stations.size());
		int costOfTransform = 0;
		if (arg.size() > 4)throw invalid_argument("wrong_number");
		if (arg.size() == 4)
		{
			if (arg[3] == L"/adv")
			{
				costOfTransform = 3;
			}
			else
			{
				throw invalid_argument("invalid_argument");
			}
		}
		wstring out;
		wchar_t buf[10000];
		for (int i = 0; i < graph.stations.size(); i++)
		{
			des[i].resize(graph.stations.size());
			for (int j = 0; j < graph.stations.size(); j++)
			{
				Route route = Search(graph.stations[i].name, graph.stations[j].name, graph, costOfTransform).SearchThePath();
				des[i][j] = route.cost;
				_itow(des[i][j], buf, 10);
				out += buf;
				out += L" ";
			}
			out += L"\n";
		}


		OutFile outfile;
		if (arg.size() == 4)
		{
			switch (city)
			{
			case City::beijing:
			{
				outfile.bind("beijing_des_adv.txt");
				break;
			}
			case City::shanghai:
			{
				outfile.bind("shanghai_des_adv.txt");
				break;
			}
			case City::small_beijing:
			{
				outfile.bind("small_beijing_des_adv.txt");
				break;
			}
			}
		}
		else
		{
			switch (city)
			{
			case City::beijing:
			{
				outfile.bind("beijing_des.txt");
				break;
			}
			case City::shanghai:
			{
				outfile.bind("shanghai_des.txt");
				break;
			}
			case City::small_beijing:
			{
				outfile.bind("small_beijing_des.txt");
				break;
			}
			}
		}
		if (!outfile.open())throw runtime_error("unable_to_open_file");
		if (outfile.puts(out.c_str()) < 0)throw runtime_error("unable_to_output_file");
		outfile.close();
	}
	case 'z':
	{
		if (argc != 4)throw invalid_argument("wrong_number");
		InFile infile(argv[3]);
		if (!infile.open())throw runtime_error("unable_to_open_file");
		wchar_t inBuf[100000];
		vector<wstring>steps;
		for (int i = 0;; i++)
		{
			if (infile.gets(inBuf, sizeof(inBuf)) == NULL)break;
			steps.push_back(wstring(inBuf));
			steps.back().pop_back();
		}
		vector<int>visited(graph.stations.size(), 0);
		int theSubwayOn = -1;
		int theStationIn = -1;
		for (int i = 1; i < steps.size(); i++)
		{
			if (theStationIn == -1)
			{
				for (int j = 0; j < graph.stations.size(); j++)
				{
					if (graph.stations[j].isEqual(steps[1].c_str()))
					{
						theStationIn = j;
						break;
					}
				}

				if (theStationIn == -1)
				{
					wcout << steps[1] << endl;
					throw runtime_error("no_such_station");
				}
				visited[theStationIn] = 1;
				continue;
			}
			if (steps[i][0] == L'乘')
			{
				wstring nameOfSubwayline;
				nameOfSubwayline = steps[i].substr(3);
				int noOfSubwayline = -1;
				for (int j = 0; j < graph.subwayLine.size(); j++)
				{
					if (graph.subwayLine[j].name == nameOfSubwayline)
					{
						noOfSubwayline = j;
						break;
					}
				}
				if (noOfSubwayline == -1)
				{
					wcout << nameOfSubwayline << endl;
					throw runtime_error("no_such_subway");
				}
				bool isExist = false;
				for (int j = 0; j < graph.stations[theStationIn].subwayLinePointer.size(); j++)
				{
					if (graph.stations[theStationIn].subwayLinePointer[j] == noOfSubwayline)
					{
						isExist = true;
						break;
					}
				}
				if (isExist)
				{
					theSubwayOn = noOfSubwayline;
				}
				else
				{
					wcout << L"cannot change to " << graph.subwayLine[noOfSubwayline].name << L" in the" << graph.stations[theStationIn].name << endl;
					throw runtime_error("invalid_transform");
				}
			}
			else
			{
				int noOfStation = -1;
				for (int j = 0; j < graph.stations.size(); j++)
				{
					if (graph.stations[j].isEqual(steps[i].c_str()))
					{
						noOfStation = j;
						break;
					}
				}
				if (noOfStation == -1)
				{
					wcout << steps[i] << endl;
					throw runtime_error("no_such_station");
				}
				int noOfLink = -1;
				for (int j = 0; j < graph.linkBetweenStation.size(); j++)
				{
					if (graph.linkBetweenStation[j].firstStation == theStationIn &&
						graph.linkBetweenStation[j].secondStation == noOfStation)
					{
						noOfLink = j;
						break;
					}
				}
				if (noOfLink == -1)
				{
					wcout << L"cannot go to " << graph.stations[noOfStation].name << L" from " << graph.stations[theStationIn].name << endl;
					throw runtime_error("no_such_link");
				}
				bool isExist = false;
				for (size_t j = 0; j < graph.linkBetweenStation[noOfLink].subwayLinePointer.size(); j++)
				{
					if (graph.linkBetweenStation[noOfLink].subwayLinePointer[j] == theSubwayOn)
					{
						isExist = true;
						break;
					}
				}
				if (isExist)
				{
					theStationIn = noOfStation;
				}
				else
				{
					wcout << L"cannot go to " << graph.stations[noOfStation].name
						<< L" from " << graph.stations[theStationIn].name
						<< L" on " << graph.subwayLine[theSubwayOn].name
						<< endl;
				}
				visited[theStationIn] = 1;
			}
		}
		for (int i = 0; i < graph.stations.size(); i++)
		{
			if (visited[i] == 0)
			{
				wcout << L"untouched" << graph.stations[i].name << endl;
				throw runtime_error("untouched_station");
			}
		}
		cout << "true" << endl;
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
	appmain(argc, argv);
	return 0;
}

