//SelectionSortStrategy.cpp
#include "../h/SelectionSortStrategy.h"
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"
#include <chrono>

//constructor
SelectionSortStrategy::SelectionSortStrategy()
{

}

//destructor
SelectionSortStrategy::~SelectionSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult SelectionSortStrategy::SortSequence(Sequence &sequence, int bound)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

    SelectionSortSequence(sequence, bound);

    std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1, 1>> dur = t2 - t1;
    sr._duration = dur.count();

    return sr;
}

//Sorts sequence of elements
void SelectionSortStrategy::SelectionSortSequence(Sequence &sequence, int bound)
{
    int left = 0;
    int right = bound - 1;
    for (int i = left; i <= right; i++)
    {
        int min = i;
        for (int j = i + 1; j <= right; j++)
        {
            if (sequence.fd.at(j) < sequence.fd.at(min))
            {
                min = j;
                sr._cmp++;
            }
            sr._cmp++;
        }
        std::swap(sequence.fd.at(i), sequence.fd.at(min));
        sr._moves++;
    }
    sr._cmp += 2;
}
