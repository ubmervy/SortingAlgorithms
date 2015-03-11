//MergeSortStrategy.cpp
#include "MergeSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
#include <chrono>

//constructor
MergeSortStrategy::MergeSortStrategy()
{

}

//destructor
MergeSortStrategy::~MergeSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult MergeSortStrategy::SortSequence(Sequence &sequence)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

	MergeSortSequence(sequence);

	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration< double, std::ratio<1, 1>> dur = t2 - t1;
	sr.duration = dur.count();

	return sr;
}

//Sorts sequence of elements by calling MergeSequence recoursively
void MergeSortStrategy::MergeSortSequence(Sequence &sequence)
{
	int left = 0;
	int right = sequence.fd.size() - 1;
	MergeSequence(sequence, left, right);
}

//Splits sequence into two parts and calls merge method for each
void MergeSortStrategy::MergeSequence(Sequence &sequence, int left, int right)
{
	if (right <= left) return;
	int m = (right + left) / 2;
	int new_left = m + 1;
	MergeSequence(sequence, left, m);
	MergeSequence(sequence, new_left, right);
	merge(sequence, left, m, right);
}

//Merges two sequences
void MergeSortStrategy::merge(Sequence &sequence, int l, int m, int r)
{
	int i, j;
	std::vector<std::string> aux(sequence.fd.size());
	//	static std::vector<std::shared_ptr<void*>> aux(sequence.fd.size());
	for (i = m + 1; i > l; --i)
	{
		aux[i - 1] = sequence.fd[i - 1];
		sr.moves++;
	}
	for (j = m; j < r; ++j)
	{
		aux[r + m - j] = sequence.fd[j + 1];
		sr.moves++;
	}
	for (int k = l; k <= r; ++k)
	{
		if (aux.at(j) < aux.at(i))
		{
			sequence.fd[k] = aux[j--];
			sr.cmp++;
			sr.moves++;
		}
		else
		{
			sequence.fd[k] = aux[i++];
			sr.moves++;
		}
		sr.cmp++;
	}
}