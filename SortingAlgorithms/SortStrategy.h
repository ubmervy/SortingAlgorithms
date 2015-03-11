//SortStrategy.h
#ifndef SortStrategy_h
#define SortStrategy_h
#include "SortResult.h"
#include "Sequence.h"

class SortStrategy
{
public:
	//constructor
	SortStrategy();

	//destructor
	~SortStrategy();

	virtual SortResult SortSequence(Sequence &sequence) = 0;
};

#endif // !SortStrategy_h
