//Context.h
#ifndef Context_h
#define Context_h
#include "SortResult.h"
#include "SortStrategy.h"
#include "Sequence.h"
#include <memory>

class Context
{
public:
    //constructor
    Context();

    //destructor
    ~Context();

    //Should set sorting algorithm
    virtual void SetSortStrategy(std::unique_ptr<SortStrategy> &sorttype) = 0;

    //Should apply sorting algorithm
    virtual SortResult ApplySortStrategy(Sequence &sequence) = 0;

protected:
    std::unique_ptr<SortStrategy> sortStrategy; //points to chosen SortStrategy object
};

#endif // !Context_h
