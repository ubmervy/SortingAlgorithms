//MergeSortStrategy.h
#ifndef MergeSortStrategy_h
#define MergeSortStrategy_h
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"

class MergeSortStrategy : public SortStrategy
{
public:
    //constructor
    MergeSortStrategy();

    //destructor
    ~MergeSortStrategy();

    const std::string alg_name = "Merge";// sorting algorithm name

    // Measures sorting time and returns SortResult
    SortResult	SortSequence(Sequence &sequence, int bound) override;

    SortResult sr { alg_name }; //Object for storing sort results

private:
    //Sorts sequence of elements by calling MergeSequence recoursively
    void MergeSortSequence(Sequence &sequence, int bound);

    //Splits sequence into two parts and calls merge method for each
    void MergeSequence(Sequence &sequence, int left, int right);

    //Merges two sequences
    void merge(Sequence &sequence, int l, int m, int r);
};
#endif // !MergeSortStrategy_h
