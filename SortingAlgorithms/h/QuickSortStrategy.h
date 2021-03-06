//QuickSortStrategy.h
#ifndef QuickSortStrategy_h
#define QuickSortStrategy_h
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"
#include <stack>

class QuickSortStrategy : public SortStrategy
{
public:
    //constructor
    QuickSortStrategy();

    //destructor
    ~QuickSortStrategy();

    const std::string alg_name = "Quick";// sorting algorithm name

    // Measures sorting time and returns SortResult
    SortResult	SortSequence(Sequence &sequence, int bound) override;

    SortResult sr { alg_name }; //Object for storing sort results

private:
    //Sorts sequence of elements
    void QuickSortSequence(Sequence &sequence, int bound);

    //Gets pivot element for quicksort
    int MakePartition(Sequence &sequence, int left, int right);

    //Pushes to stack minimal part of divided sequence to minimize stack size
    void PushToStack(std::stack<int> &s, int &A, int &B) const;
};
#endif // !QuickSortStrategy_h
