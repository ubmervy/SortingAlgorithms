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

class QuickSort : public SortStrategy
{
public:
	QuickSort(){}
	~QuickSort(){}

	const std::string alg_name = "QuickSort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

		QuickSortSequence(sequence);

		std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
		sr.duration = dur.count();

		return sr;
	}

private:
	void QuickSortSequence(Sequence &sequence)
	{
		int left = 0;
		int right = sequence.fd.size() - 1;
		std::stack <int> st;
		st.push(right);
		st.push(left);
		int maxStack = st.size() / 2;

		while (!st.empty())
		{
			left = st.top();
			st.pop();
			right = st.top();
			st.pop();
			if (right <= left)
			{
				//cmp++;
				continue;
			}
			int i = MakePartition(sequence, left, right);

			//push2(s, l, i - 1);
			//push2(s, i + 1, r);

			//push2(s, i + 1, r);
			//push2(s, l, i - 1);

			if (i - left > right - i)
			{
				sr.cmp++;
				PushToStack(st, left, --i);
				PushToStack(st, ++i, right);
			}
			else
			{
				PushToStack(st, ++i, right);
				PushToStack(st, left, --i);
			}
			if (st.size() / 2 > (unsigned)maxStack)
			{
				maxStack = st.size() / 2;
				sr.cmp++;
			}
		}
	}

	int MakePartition(Sequence &sequence, int left, int right)
	{
		int i = left - 1, j = right;
		std::string v = sequence.fd[right];
		//std::shared_ptr<void> v = sequence.fd.at(right);
		for (;;)
		{
			while (sequence.fd[++i] < v)
			{
				sr.cmp++;
			};
			sr.cmp++;
			while (v < sequence.fd.at(--j))
			{
				sr.cmp++;
				if (j == left)
				{
					break;
				}
			}
			sr.cmp++;
			if (i >= j)
			{
				sr.cmp++;
				break;
			}
			sr.cmp++;

			std::swap(sequence.fd[i], sequence.fd[j]);
			sr.moves++;
		}
		std::swap(sequence.fd[i], sequence.fd[right]);
		sr.moves++;
		return i;
	}

	void PushToStack(std::stack<int> &s, int &A, int &B) const
	{
		s.push(B);
		s.push(A);
	}
};

class MergeSort : public SortStrategy
{
public:
	MergeSort(){}
	~MergeSort(){}

	const std::string alg_name = "MergeSort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

		MergeSortSequence(sequence);

		std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
		sr.duration = dur.count();

		return sr;
	}

private:

	void MergeSortSequence(Sequence &sequence)
	{
		int left = 0;
		int right = sequence.fd.size() - 1;
		MergeSequence(sequence, left, right);
	}

	void MergeSequence(Sequence &sequence, int left, int right)
	{
		if (right <= left) return;
		int m = (right + left) / 2;
		int new_left = m + 1;
		MergeSequence(sequence, left, m);
		MergeSequence(sequence, new_left, right);
		merge(sequence, left, m, right);
	};

	void merge(Sequence &sequence, int l, int m, int r)
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
};

class HeapSort : public SortStrategy
{
public:
	HeapSort(){}
	~HeapSort(){}

	const std::string alg_name = "HeapSort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

		HeapSortSequence(sequence);

		std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration< double, std::ratio<1, 1>> dur = t2 - t1;
		sr.duration = dur.count();

		return sr;
	}

private:
	void HeapSortSequence(Sequence &sequence)
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

	void fixDown(Sequence &sequence, int k, int N)
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

};

class ShellSort : public SortStrategy
{
public:
	ShellSort(){}
	~ShellSort(){}

	const std::string alg_name = "ShellSort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

		ShellSortSequence(sequence);

		std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
		sr.duration = dur.count();

		return sr;
	}

private:

	void ShellSortSequence(Sequence &sequence)
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
	int defineMoreGaps(int n, int i) const
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

};

class Context
{
protected:
	std::unique_ptr<SortStrategy> sortStrategy;

public:
	Context(){}
	~Context(){}

	virtual void SetSortStrategy(std::unique_ptr<SortStrategy> &sorttype) = 0;
	virtual SortResult ApplySortStrategy(Sequence &sequence) = 0;
};

//load text data from file, delete punctuation and create vector of words
class FileLoader
{
public:

	FileLoader(){};
	FileLoader(FileLoader& other){};

	~FileLoader(){};

	//get string string from file data
	std::string GetFileData(std::string& srcpath)
	{
		std::string data;
		std::ifstream in(srcpath, std::ios::in);
		data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());
		return data;
	}

	//write sorted data to a file
	void WriteToFile(const std::string& dstpath, Sequence& sequence)
	{
		std::ofstream out(dstpath);
		if (out.is_open())
		{
			std::vector<std::string>::iterator it;
			for (it = sequence.fd.begin(); it != sequence.fd.end(); ++it)
			{
				out << *it << std::endl;
			}
			out.close();
		}
	}

	/*CopyFromTo(std::string& srcpath, std::string& dstpath)
		{
		std::ifstream source(srcpath, std::ios::binary);
		std::ofstream dest(dstpath, std::ios::binary);

		// file size
		source.seekg(0, std::ios::end);
		std::ifstream::pos_type size = source.tellg();
		source.seekg(0);
		// allocate memory for buffer
		char* buffer = new char[size];

		// copy file
		source.read(buffer, size);
		dest.write(buffer, size);

		// clean up
		delete[] buffer;
		source.close();
		dest.close();
		}*/
};

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
		_strategies["hs"] = std::unique_ptr<SortStrategy>(new HeapSort);
		_strategies["ins"] = std::unique_ptr<SortStrategy>(new InsertionSortStrategy);
		_strategies["ms"] = std::unique_ptr<SortStrategy>(new MergeSort);
		_strategies["qs"] = std::unique_ptr<SortStrategy>(new QuickSort);
		_strategies["shs"] = std::unique_ptr<SortStrategy>(new ShellSort);
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
