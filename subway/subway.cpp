#include "pch.h"
#include <iostream>
#include"init.h"
#include"Utility.h"

int getArg(int argc, char* argv[])
{

	return 0;
}

int appmain(int argc, char* argv[])
{
	init(City::beijing);
	getArg(argc, argv);
	return 0;
}

int main(int argc, char* argv[])
{
	appmain(argc,argv);
	return 0;
}

