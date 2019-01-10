#include"pch.h"
#include "IO.h"

InFile::InFile(void)
{
	strcpy(route, "");
	open();
}

InFile::InFile(const char desroute[])
{
	strcpy(route, desroute);
}

bool InFile::bind(const char desroute[])
{
	if (strlen(desroute) < 1000)
	{
		strcpy(route, desroute);
		return true;
	}
	else return false;
}

bool InFile::open()
{
	if (fp == NULL)
		fp = fopen(route, "r+");
	return (fp != NULL);
}

wchar_t *InFile::gets(wchar_t *des, int n)
{
	return fgetws(des, n, fp);
}

int InFile::close()
{
	if (fp != NULL)return fclose(fp);
	else return 0;
}

InFile::~InFile(void)
{
	if (fp != NULL)fclose(fp);
}

OutFile::OutFile(void)
{
	strcpy(route, "");
}

OutFile::OutFile(const char desroute[])
{
	strcpy(route, desroute);
	open();
}

bool OutFile::bind(const char desroute[])
{
	if (strlen(desroute) < 1000)
	{
		strcpy(route, desroute);
		return true;
	}
	else return false;
}

bool OutFile::open()
{
	if (fp == NULL) fp = fopen(route, "w+");
	return (fp != NULL);
}

int OutFile::puts(const wchar_t *sou)
{
	return fputws(sou, fp);

}

int OutFile::close()
{
	if (fp != NULL)return fclose(fp);
	else return 0;
}

OutFile::~OutFile(void)
{
	if (fp != NULL)fclose(fp);
}
