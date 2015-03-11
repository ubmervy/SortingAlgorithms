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
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale.h>
#include <memory>
#include <stack>
#include <chrono>
#include <thread>
#include <cstring>

//constructor
FileSorter::FileSorter(std::string& srcpath, std::string& dstpath, bool stable = 1) :
_sortresults{},
_strategies{},
_srcpath(srcpath),
_dstpath(dstpath),
_stable(stable),
_memory(1),
_fileObject()
{
	Sequence sequence{ _fileObject.GetFileData(_srcpath) };
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
	_strategies["hs"] = std::unique_ptr<SortStrategy>(new HeapSortStrategy);
	_strategies["ins"] = std::unique_ptr<SortStrategy>(new InsertionSortStrategy);
	_strategies["ms"] = std::unique_ptr<SortStrategy>(new MergeSortStrategy);
	_strategies["qs"] = std::unique_ptr<SortStrategy>(new QuickSortStrategy);
	_strategies["shs"] = std::unique_ptr<SortStrategy>(new ShellSortStrategy);
	_strategies["sls"] = std::unique_ptr<SortStrategy>(new SelectionSortStrategy);

	if (test)
	{
		std::unique_ptr<SortStrategy> recommendedStrategy = std::move(_strategies[RecommendStrategy(sequence)]);
		SetSortStrategy(recommendedStrategy);
		_sortresults.push_back(ApplySortStrategy(sequence));
	}
	else
	{

		std::map<std::string, std::unique_ptr<SortStrategy>>::iterator it;
		for (it = _strategies.begin(); it != _strategies.end(); ++it)
		{
			std::unique_ptr<SortStrategy> currentStrategy = std::move((*it).second);;
			SetSortStrategy(currentStrategy);
			_sortresults.push_back(ApplySortStrategy(sequence));
		}
	}
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
		return "ins";
	}
	else if (sequence.fd.size() > 100 && sequence.fd.size() < 1000)
	{
		if (_stable)
		{
			return "qs";
		}
		else
		{
			return "shs";
		}
	}
	else
	{
		if (!_memory)
		{
			if (_stable)
			{
				return "qs";
			}
			else
			{
				return "hs";
			}
		}
		return "ms";
	}
}

	//Writes results of sorting - to output file and on the screen
void FileSorter::WriteResult(Sequence &sequence)
{
	_fileObject.WriteToFile(_dstpath, sequence);
	std::cout << "number of elements: " << sequence.fd.size() << '\n' << std::endl;
	for (unsigned int i = 0; i < _sortresults.size(); ++i)
	{
		std::cout << "sorting algorithm: " << _sortresults.at(i).sorttype << std::endl;
		std::cout << "number of moves (exchanges): " << _sortresults.at(i).moves << std::endl;
		std::cout << "number of compares: " << _sortresults.at(i).cmp << std::endl;
		std::cout << "sorting duration: " << _sortresults.at(i).duration << std::endl << std::endl;
		std::cout << std::endl;
	}

	/*std::vector<std::string>::iterator cur;
	//std::vector<std::shared_ptr<void>>::iterator cur;
	for (cur = sequence.fd.begin(); cur < sequence.fd.end(); ++cur)
	{
	std::cout << *cur << std::endl;
	}*/
}
