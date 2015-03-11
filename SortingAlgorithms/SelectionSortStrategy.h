//SelectionSortStrategy.h
#ifndef SelectionSortStrategy_h
#define SelectionSortStrategy_h
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"

class SelectionSortStrategy : public SortStrategy
{
public:
	//constructor
	SelectionSortStrategy();

	//destructor
	~SelectionSortStrategy();

	// sorting algorithm name
	const std::string alg_name = "Selection Sort";

	// Measures sorting time and returns SortResult
	SortResult	SortSequence(Sequence &sequence) override;
	
	SortResult sr{ alg_name }; //Object for storing sort results

private:
	//Sorts sequence of elements
	void SelectionSortSequence(Sequence &sequence);
};
#endif // !SelectionSortStrategy_h
