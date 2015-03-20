//InsertionSortStrategy.cpp
#include "../h/InsertionSortStrategy.h"
#include "../h/SortStrategy.h"
#include "../h/SortResult.h"
#include "../h/Sequence.h"
#include <chrono>

//constructor
InsertionSortStrategy::InsertionSortStrategy()
{

}

//destructor
InsertionSortStrategy::~InsertionSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult InsertionSortStrategy::SortSequence(Sequence &sequence, int bound)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

    InsertionSortSequence(sequence, bound);

    std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
    sr._duration = dur.count();

    return sr;
}

//Sorts sequence of elements
void InsertionSortStrategy::InsertionSortSequence(Sequence &sequence, int bound)
{
    int left = 0;
    int right = bound - 1;
    for (int i = left + 1; i <= right; i++)
    {
        int j = i;
        auto v = sequence.fd.at(j);
        while (j > left && v < sequence.fd.at(j - 1))
        {
            sequence.fd[j] = sequence.fd[j - 1];
            j--;
            sr._cmp += 2;
            sr._moves++;
        }
        sr._cmp += 2;
        sr._moves++;
        sequence.fd[j] = v;
    }
}
