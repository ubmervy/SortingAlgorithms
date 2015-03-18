//SortResult.cpp
#include "../h/SortResult.h"

//constructor
SortResult::SortResult(std::string st, double dur, int cm, int mv) :
    _sorttype(st),
    _duration(dur),
    _cmp(cm),
    _moves(mv)
{

}

//copy constructor
SortResult::SortResult(const SortResult& other_sortresult):
    _sorttype(other_sortresult._sorttype),
    _duration(other_sortresult._duration),
    _cmp(other_sortresult._cmp),
    _moves(other_sortresult._moves)
{

}

//destructor
SortResult::~SortResult()
{

}

bool SortResult::operator <(const SortResult& val) const
{
    return this->_duration < val._duration;
}
