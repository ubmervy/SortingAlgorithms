//HeapSortStrategy.h
#ifndef HeapSortStrategy_h
#define HeapSortStrategy_h
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"

class HeapSortStrategy : public SortStrategy
{
public:
	//constructor
	HeapSortStrategy();

	//destructor
	~HeapSortStrategy();

	const std::string alg_name = "Heap Sort";// sorting algorithm name

	// Measures sorting time and returns SortResult
	SortResult	SortSequence(Sequence &sequence) override;

	SortResult sr{ alg_name }; //Object for storing sort results

private:
	//Sorts sequence of elements
	void HeapSortSequence(Sequence &sequence);

	//Balances heap subtrees
	void fixDown(Sequence &sequence, int k, int N);

};
#endif // !HeapSortStrategy_h