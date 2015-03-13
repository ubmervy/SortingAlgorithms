//SortResult.cpp
#include "SortResult.h"

//constructor
SortResult::SortResult(std::string st, double dur, int cm, int mv) :
    sorttype(st),
    duration(dur),
    cmp(cm),
    moves(mv)
{

}

//copy constructor
SortResult::SortResult(const SortResult& other_sortresult):
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

bool SortResult::operator <(const SortResult& val) const
{
    return duration < val.duration;
}
