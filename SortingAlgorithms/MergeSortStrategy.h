//MergeSortStrategy.h
#ifndef MergeSortStrategy_h
#define MergeSortStrategy_h
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"

class MergeSortStrategy : public SortStrategy
{
public:
	//constructor
	MergeSortStrategy();

	//destructor
	~MergeSortStrategy();

	// sorting algorithm name
	const std::string alg_name = "Merge Sort";

	// Measures sorting time and returns SortResult
	SortResult	SortSequence(Sequence &sequence) override;

	SortResult sr{ alg_name }; //Object for storing sort results

private:
	//Sorts sequence of elements by calling MergeSequence recoursively
	void MergeSortSequence(Sequence &sequence);

	//Splits sequence into two parts and calls merge method for each
	void MergeSequence(Sequence &sequence, int left, int right);

	//Merges two sequences
	void merge(Sequence &sequence, int l, int m, int r);
};
#endif // !MergeSortStrategy_h