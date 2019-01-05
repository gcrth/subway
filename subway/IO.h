#pragma once
#include "pch.h"
#include <iostream>
#include <string.h>

class InFile
{
private:
	FILE *fp = NULL;
	char route[1010];
public:
	InFile(void);
	InFile(const char desroute[]);
	bool bind(const char desroute[]);
	bool open();
	wchar_t *gets(wchar_t *des, int n = 18);
	int close();
	~InFile(void);
};

class OutFile
{
private:
	FILE *fp = NULL;
	char route[1010];
public:
	OutFile(void);
	OutFile(const char desroute[]);
	bool bind(const char desroute[]);
	bool open();
	int puts(const char *sou);
	int close();
	~OutFile(void);
};

