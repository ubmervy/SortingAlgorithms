//InsertionSortStrategy.h
#ifndef InsertionSortStrategy_h
#define InsertionSortStrategy_h
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"

class InsertionSortStrategy : public SortStrategy
{
public:
    //constructor
    InsertionSortStrategy();

    //destructor
    ~InsertionSortStrategy();

    const std::string alg_name = "Insertion"; // sorting algorithm name

    // Measures sorting time and returns SortResult
    SortResult SortSequence(Sequence &sequence, int bound) override;

    SortResult sr { alg_name }; //Object for storing sort results

private:
    //Sort sequence of elements
    void InsertionSortSequence(Sequence &sequence, int bound);
};

#endif // !InsertionSortStrategy_h
