//HeapSortStrategy.cpp
#include "HeapSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
#include <chrono>

//constructor
HeapSortStrategy::HeapSortStrategy()
{

}

//destructor
HeapSortStrategy::~HeapSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult HeapSortStrategy::SortSequence(Sequence &sequence)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

	HeapSortSequence(sequence);

	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration< double, std::ratio<1, 1>> dur = t2 - t1;
	sr.duration = dur.count();

	return sr;
}

//Sorts sequence of elements
void HeapSortStrategy::HeapSortSequence(Sequence &sequence)
{
	int k, N = sequence.fd.size() - 1;
	int left = 0;
	int right = sequence.fd.size() - 1;

	int position_delta = left - 1;
	for (k = N / 2; k >= 1; --k)
	{
		fixDown(sequence, k, N);
	}
	while (N > 1)
	{
		int begin = position_delta + 1;
		int end = position_delta + N;
		std::swap(sequence.fd.at(begin), sequence.fd.at(end));
		sr.moves++;
		fixDown(sequence, 1, --N);
	}
}

//Balances heap subtrees
void HeapSortStrategy::fixDown(Sequence &sequence, int k, int N)
{
	while (2 * k <= N)
	{
		int j = 2 * k;
		if (j < N && sequence.fd.at(j) < sequence.fd.at(j + 1))
		{
			j++;
			sr.cmp += 2;
		}
		if (sequence.fd[k] < sequence.fd[j])
		{
			sr.cmp += 2;
			break;
		}
		std::swap(sequence.fd[k], sequence.fd[j]);
		sr.moves++;
		k = j;
	}
}

