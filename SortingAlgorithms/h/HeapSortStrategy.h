//HeapSortStrategy.h
#ifndef HeapSortStrategy_h
#define HeapSortStrategy_h
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"

class HeapSortStrategy : public SortStrategy
{
public:
    //constructor
    HeapSortStrategy();

    //destructor
    ~HeapSortStrategy();

    const std::string alg_name = "Heap";// sorting algorithm name

    // Measures sorting time and returns SortResult
    SortResult	SortSequence(Sequence &sequence, int bound) override;

    SortResult sr { alg_name }; //Object for storing sort results

private:
    //Sorts sequence of elements
    void HeapSortSequence(Sequence &sequence, int bound);

    //Balances heap subtrees
    void fixDown(Sequence &sequence, int k, int N);

};
#endif // !HeapSortStrategy_h
