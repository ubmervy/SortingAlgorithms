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

#include "Sequence.h"
#include "SortResult.h"
#include "SortStrategy.h"
#include "SelectionSortStrategy.h"
#include "InsertionSortStrategy.h"
#include "QuickSortStrategy.h"
#include "MergeSortStrategy.h"
#include "HeapSortStrategy.h"
#include "ShellSortStrategy.h"
#include "Context.h"
#include "FileLoader.h"

class FileSorter : public Context
{
public:

	FileSorter() {}

	FileSorter(std::string& srcpath, std::string& dstpath, bool stable = 1) :
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

	~FileSorter() {}

	std::map<std::string, std::unique_ptr<SortStrategy>> _strategies;
	std::vector<SortResult> _sortresults;

	void SortFile(Sequence &sequence, bool stable = 1, bool memory = 1, bool test = 1)
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
	};

private:
	std::string _srcpath;
	std::string _dstpath;
	bool _stable;
	bool _memory;
	FileLoader _fileObject;

	void SetSortStrategy(std::unique_ptr<SortStrategy> &strategy) override
	{
		sortStrategy.reset(nullptr);
		sortStrategy = std::move(strategy);
	}

	SortResult ApplySortStrategy(Sequence &sequence) override
	{
		return sortStrategy->SortSequence(sequence);
	}

	std::string RecommendStrategy(Sequence &sequence)
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

	void WriteResult(Sequence &sequence)
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
};

int main(int argc, char* argv[])
{
	std::string inFilePath;
	std::string outFilePath = "sorted";

	if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is\n -in <input file path> \n -o <output file name> (or it will be saved in sorted.txt)\n -s <stable sorting is required> "; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	}
	else
	{ // if we've got enough parameters
		for (int i = 1; i < argc; ++i)
		{
			if (std::string(argv[i]) == "-in")
			{
				inFilePath = std::string(argv[i + 1]);
				++i;
			}
			else if (std::string(argv[i]) == "-o")
			{
				outFilePath = std::string(argv[i + 1]);
				++i;
			}
			else {
				std::cout << "Not enough or invalid arguments, please try again.\n";
				std::this_thread::sleep_for(std::chrono::seconds(10));
				exit(0);
			}
		}
	}

	if (inFilePath == "" | outFilePath == "")
	{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Please, enter path to input file with -in option. \n"; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	}
	else
	{
		FileSorter file(inFilePath, outFilePath, 0);
	}

	_getch();
	return 0;
};
