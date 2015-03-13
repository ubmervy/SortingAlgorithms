//SelectionSortStrategy.cpp
#include "SelectionSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
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
SortResult SelectionSortStrategy::SortSequence(Sequence &sequence)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

    SelectionSortSequence(sequence);

    std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1, 1>> dur = t2 - t1;
    sr.duration = dur.count();

    return sr;
}

//Sorts sequence of elements
void SelectionSortStrategy::SelectionSortSequence(Sequence &sequence)
{
    int left = 0;
    int right = sequence.fd.size() - 1;
    for (int i = left; i <= right; i++)
    {
        int min = i;
        for (int j = i + 1; j <= right; j++)
        {
            if (sequence.fd.at(j) < sequence.fd.at(min))
            {
                min = j;
                sr.cmp++;
            }
            sr.cmp++;
        }
        std::swap(sequence.fd.at(i), sequence.fd.at(min));
        sr.moves++;
    }
    sr.cmp += 2;
}
