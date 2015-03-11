//InsertionSortStrategy.cpp
#include "InsertionSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
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
SortResult InsertionSortStrategy::SortSequence(Sequence &sequence)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

	InsertionSortSequence(sequence);

	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
	sr.duration = dur.count();

	return sr;
}

//Sorts sequence of elements
void InsertionSortStrategy::InsertionSortSequence(Sequence &sequence)
{
	int left = 0;
	int right = sequence.fd.size() - 1;
	for (int i = left + 1; i <= right; i++)
	{
		int j = i;
		auto v = sequence.fd.at(j);
		while (j > left && v < sequence.fd.at(j - 1))
		{
			sequence.fd[j] = sequence.fd[j - 1];
			j--;
			sr.cmp += 2;
			sr.moves++;
		}
		sr.cmp += 2;
		sr.moves++;
		sequence.fd[j] = v;
	}
}