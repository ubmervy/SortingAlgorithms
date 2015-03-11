//SortResult.cpp
#include "SortResult.h"

//constructor
SortResult::SortResult(std::string st, double dur = 0.0, int cm = 0, int mv = 0) :
duration(dur),
sorttype(st),
cmp(cm),
moves(mv)
{
	SetSortType(st);
}

//copy constructor
SortResult::SortResult(const SortResult& other_sortresult) :
sorttype(other_sortresult.sorttype),
duration(other_sortresult.duration),
cmp(other_sortresult.cmp),
moves(other_sortresult.moves)
{

}

//destructor
SortResult::~SortResult()
{

}

//set name of used sorting algorithm
void SortResult::SetSortType(std::string& s)
{
	sorttype = s;
}