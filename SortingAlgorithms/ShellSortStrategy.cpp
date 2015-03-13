//ShellSortStrategy.cpp
#include "ShellSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
#include <chrono>
#include <math.h>

//constructor
ShellSortStrategy::ShellSortStrategy()
{

}

//destructor
ShellSortStrategy::~ShellSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult ShellSortStrategy::SortSequence(Sequence &sequence)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

    ShellSortSequence(sequence);

    std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double, std::ratio<1, 1>> dur = t2 - t1;
    sr.duration = dur.count();

    return sr;
}

//Sorts sequence of elements
void ShellSortStrategy::ShellSortSequence(Sequence &sequence)
{
    int cm[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 }; // Ì.Ciura’s sequence for Shell sort
    int left = 0;
    int right = sequence.fd.size() - 1;
    int n = right - left + 1;
    int gap, i, j;
    std::vector<int> gaps;

    int itertions = 0;

    //form vector of gaps
    while (n > 3 * cm[8 - itertions])
    {
        gaps.push_back(cm[8 - itertions]);
        if (itertions == 8)
        {
            while (n > 3 * gaps.back())
            {
                gap = defineMoreGaps(n, itertions);
                gaps.push_back(gap);
            }
            break;
        }
        itertions++;
    }

    //sort sequence
    while (!gaps.empty())
    {
        gap = gaps.back();

        for (i = 0; i < (n - gap); i++)
        {
            j = i;
            while (j >= 0 && sequence.fd.at(j) > sequence.fd.at(j + gap))
            {
                std::swap(sequence.fd.at(j), sequence.fd.at(j + gap));
                j -= gap;
                sr.cmp += 2;
                sr.moves++;
            }
            sr.cmp += 2;
            sr.moves++;
        }
        gaps.pop_back();
    }
}

//calculate gaps for h-sorting if 3*N > max of A102549 sequence
int ShellSortStrategy::defineMoreGaps(int n, int i)
{
    double d = 0;
    if (i % 2)
    {
        d = round((8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1));
    }
    else
    {
        d = round((9 * pow(2, i) - 9 * pow(2, i / 2) + 1));
    }
    return (int)d;
}
