//FileSorter.cpp
#include "FileSorter.h"
#include "Context.h"
#include "FileLoader.h"
#include "SortResult.h"
#include "SortStrategy.h"
#include "SelectionSortStrategy.h"
#include "InsertionSortStrategy.h"
#include "QuickSortStrategy.h"
#include "MergeSortStrategy.h"
#include "HeapSortStrategy.h"
#include "ShellSortStrategy.h"
#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale.h>
#include <memory>
#include <stack>
#include <cstring>

//constructor
FileSorter::FileSorter(std::string &srcpath, std::string &dstpath, bool stable) :
_sortresults{},
_strategies{},
_srcpath(srcpath),
_dstpath(dstpath),
_stable(stable),
_memory(1),
_fileObject{}
{
	std::string d = _fileObject.GetFileData(_srcpath);
	Sequence sequence{ d };
	_recommendedStrategy = RecommendStrategy(sequence);
	SortFile(sequence, _stable, _memory, 0);
	WriteResult(sequence);
}

//destructor
FileSorter::~FileSorter()
{

}

//Initiates and manages sorting process
void FileSorter::SortFile(Sequence &sequence, bool stable = 1, bool memory = 1, bool test = 1)
{
	_strategies["Heap"] = std::unique_ptr<SortStrategy>(new HeapSortStrategy);
	_strategies["Insertion"] = std::unique_ptr<SortStrategy>(new InsertionSortStrategy);
	_strategies["Merge"] = std::unique_ptr<SortStrategy>(new MergeSortStrategy);
	_strategies["Quick"] = std::unique_ptr<SortStrategy>(new QuickSortStrategy);
	_strategies["Shell"] = std::unique_ptr<SortStrategy>(new ShellSortStrategy);
	_strategies["Selection"] = std::unique_ptr<SortStrategy>(new SelectionSortStrategy);

	

	/*if (test)
	{
		std::unique_ptr<SortStrategy> recommendedStrategy = std::move(_strategies[RecommendStrategy(sequence)]);
		SetSortStrategy(recommendedStrategy);
		_sortresults.push_back(ApplySortStrategy(sequence));
	}
	else
	{*/

		std::map<std::string, std::unique_ptr<SortStrategy>>::iterator it;
		for (it = _strategies.begin(); it != _strategies.end(); ++it)
		{
			std::unique_ptr<SortStrategy> currentStrategy = std::move((*it).second);;
			SetSortStrategy(currentStrategy);
			_sortresults.push_back(ApplySortStrategy(sequence));
		}
	//}
}

	//Sets context according to given SortStrategy object
void FileSorter::SetSortStrategy(std::unique_ptr<SortStrategy> &strategy)
{
	sortStrategy.reset(nullptr);
	sortStrategy = std::move(strategy);
}

	//Applies SortSequence method according to current context
SortResult FileSorter::ApplySortStrategy(Sequence &sequence)
{
	return sortStrategy->SortSequence(sequence);
}

	//Analizes which algorithm suits best for sorting input sequence
std::string FileSorter::RecommendStrategy(Sequence &sequence)
{
	if (sequence.fd.size() < 100)
	{
		return "Insertion";
	}
	else if (sequence.fd.size() > 100 && sequence.fd.size() < 1000)
	{
		if (_stable)
		{
			return "Quick";
		}
		else
		{
			return "Shell";
		}
	}
	else
	{
		if (!_memory)
		{
			if (_stable)
			{
				return "Quick";
			}
			else
			{
				return "Heap";
			}
		}
		return "Merge";
	}
}

	//Writes results of sorting - to output file and on the screen
void FileSorter::WriteResult(Sequence &sequence)
{
	// write sorted sequence to file at _dstpath
	_fileObject.WriteToFile(_dstpath, sequence);

	// print statistics 
	std::cout << "number of elements: " << sequence.fd.size() << '\n' << std::endl;

	if(_stable) std::cout << "stable sorting is required" << '\n' << std::endl;

	for (unsigned int i = 0; i < _sortresults.size(); ++i)
	{
		if (_sortresults.at(i).sorttype == _recommendedStrategy) std::cout << "sorting algorithm: " << _sortresults.at(i).sorttype << " Sort (recommended)" << std::endl;
			else std::cout << "sorting algorithm: " << _sortresults.at(i).sorttype << " Sort" << std::endl;
		std::cout << "number of moves (exchanges): " << _sortresults.at(i).moves << std::endl;
		std::cout << "number of compares: " << _sortresults.at(i).cmp << std::endl;
		std::cout << "sorting duration: " << _sortresults.at(i).duration << " sec" << std::endl << std::endl;
		std::cout << std::endl;
	}

	/*std::vector<std::string>::iterator cur;
	//std::vector<std::shared_ptr<void>>::iterator cur;
	for (cur = sequence.fd.begin(); cur < sequence.fd.end(); ++cur)
	{
	std::cout << *cur << std::endl;
	}*/
}
