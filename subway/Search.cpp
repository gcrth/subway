#include "pch.h"
#include "Search.h"


Search::Search()
{
}


Search::~Search()
{
}

Search::Search(wstring from_, wstring to_)
{
	from = from_;
	to = to_;
}

Search::Search(wstring from_)
{
	from = from_;
}

int Search::SearchThePath()
{
	return 0;
}

int Search::SearchTheTraversal()
{
	return 0;
}
