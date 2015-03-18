//ShellSortStrategy.h
#ifndef ShellSortStrategy_h
#define ShellSortStrategy_h
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"

class ShellSortStrategy : public SortStrategy
{
public:
    //constructor
    ShellSortStrategy();

    //destructor
    ~ShellSortStrategy();

    const std::string alg_name = "Shell";// sorting algorithm name

    // Measures sorting time and returns SortResult
    SortResult	SortSequence(Sequence &sequence) override;

    SortResult sr { alg_name }; //Object for storing sort results

private:
    //Sorts sequence of elements
    void ShellSortSequence(Sequence &sequence);

    //calculate gaps for h-sorting if 3*N > max of A102549 sequence
    int defineMoreGaps(int n, int i);

};
#endif // !ShellSortStrategy_h
