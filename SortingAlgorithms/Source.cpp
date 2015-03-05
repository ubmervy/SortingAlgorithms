#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale.h>
#include <memory>
#include <stack>
#include <chrono>

class Sequence
{
public:
	Sequence(std::string &data, bool stable, bool memory, char datatype = 's') :
		_data(data),
		_datatype(datatype),
		_stable_sign(stable),
		_memory_sign(memory)
	{
		CreateSequence(_data, _datatype);
	};

	//copy constructor of Sequence
	Sequence(const Sequence& other_sequence) :
		_data(other_sequence._data),
		_datatype(other_sequence._datatype),
		_stable_sign(other_sequence._stable_sign),
		_memory_sign(other_sequence._memory_sign)
	{
		/*		int_filedata = other_sequence.int_filedata;
				string_filedata = other_sequence.string_filedata;
				double_filedata = other_sequence.double_filedata;*/
		fd = other_sequence.fd;
	}

	// move constructor of Sequence
	Sequence(Sequence&& other_sequence) :
		_data(""),
		_datatype('\0'),
		_stable_sign('\0'),
		_memory_sign('\0')
	{
		swap(other_sequence);
		release(other_sequence);
	}

	void swap(Sequence &other_sequence) throw ()
	{
		std::swap(this->_data, other_sequence._data);
		std::swap(this->_datatype, other_sequence._datatype);
		std::swap(this->_stable_sign, other_sequence._stable_sign);
		std::swap(this->_memory_sign, other_sequence._memory_sign);

		/*		std::swap(this->int_filedata, other_sequence.int_filedata);
				std::swap(this->string_filedata, other_sequence.string_filedata);
				std::swap(this->double_filedata, other_sequence.double_filedata);*/
		std::swap(this->fd, other_sequence.fd);
	}

	void release(Sequence &other_sequence)
	{
		other_sequence._data = "";
		other_sequence._datatype = '\0';
		other_sequence._stable_sign = '\0';
		other_sequence._memory_sign = '\0';

		/*other_sequence.int_filedata.clear();
		other_sequence.int_filedata.shrink_to_fit();
		other_sequence.string_filedata.clear();
		other_sequence.string_filedata.shrink_to_fit();
		other_sequence.double_filedata.clear();
		other_sequence.double_filedata.shrink_to_fit();*/
		other_sequence.fd.clear();
		other_sequence.fd.shrink_to_fit();
	}


	Sequence operator=(Sequence&& other_sequence)
	{
		if (this != &other_sequence)
		{
			release(*this);
			swap(other_sequence);
			release(other_sequence);
		}

		return *this;
	}

	~Sequence(){};

	std::string _data;
	char _datatype;

	/*std::vector<int> int_filedata;
	std::vector<std::string> string_filedata;
	std::vector<double> double_filedata;*/

	std::vector<std::string> fd;
	//std::vector<std::shared_ptr<void>> fd;

	bool _stable_sign; // stability result is required;
	bool _memory_sign; // additional memory for sorting is available;

	void CreateSequence(std::string data, char datatype)
	{
		//convert text to lower case
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);

		//set up and apply locale object
		std::stringstream inputStringStream(data);
		inputStringStream.imbue(std::locale(inputStringStream.getloc(), std::unique_ptr<ListOfSpaces>(new ListOfSpaces).release()));

		std::string token;
		//void* token;
		//fill vector with tokens
		while (inputStringStream >> token)
		{
			fd.push_back(token);
			/*int* pi;
			std::string* ps;
			double* pd;
			//fd.push_back(static_cast<std::shared_ptr<void*>>(token));
			switch (datatype)
			{
			case 'i':
			pi = reinterpret_cast<int*>(token);
			int_filedata.push_back(*pi);
			fd.push_back(std::make_shared<void>(int_filedata.at(int_filedata.size() - 1)));
			break;
			case 's':
			ps = reinterpret_cast<std::string*>(token);
			string_filedata.push_back(*ps);
			fd.push_back(std::make_shared<void>(string_filedata.at(string_filedata.size() - 1)));
			break;
			case 'd':
			pd = reinterpret_cast<double*>(token);
			double_filedata.push_back(*pd);
			fd.push_back(std::make_shared<void>(double_filedata.at(double_filedata.size() - 1)));
			break;
			}*/
		}
	}

private:

	//set up table of delimiters to delete
	struct ListOfSpaces : std::ctype < char >
	{
		ListOfSpaces() : std::ctype<char>(DelimsTable())
		{
		}

		static mask const* DelimsTable()
		{
			static mask rc[table_size];
			rc[':'] = std::ctype_base::space;
			rc[';'] = std::ctype_base::space;
			rc[' '] = std::ctype_base::space;
			rc['.'] = std::ctype_base::space;
			rc['-'] = std::ctype_base::space;
			rc['('] = std::ctype_base::space;
			rc[')'] = std::ctype_base::space;
			rc['+'] = std::ctype_base::space;
			rc['/'] = std::ctype_base::space;
			rc['"'] = std::ctype_base::space;
			rc['{'] = std::ctype_base::space;
			rc['}'] = std::ctype_base::space;
			rc['@'] = std::ctype_base::space;
			rc['#'] = std::ctype_base::space;
			rc['$'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['\t'] = std::ctype_base::space;
			rc['\n'] = std::ctype_base::space;
			rc[';'] = std::ctype_base::space;
			rc['~'] = std::ctype_base::space;
			rc['¹'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['*'] = std::ctype_base::space;
			rc['['] = std::ctype_base::space;
			rc[']'] = std::ctype_base::space;
			rc['='] = std::ctype_base::space;
			rc['“'] = std::ctype_base::space;
			rc['&'] = std::ctype_base::space;
			rc['\''] = std::ctype_base::space;
			rc[','] = std::ctype_base::space;
			rc['<'] = std::ctype_base::space;
			rc['>'] = std::ctype_base::space;
			rc['\\'] = std::ctype_base::space;
			rc['^'] = std::ctype_base::space;
			rc['|'] = std::ctype_base::space;

			return &rc[0];
		}
	};
};

class SortResult
{
public:

	//default constructor of SortResult
	SortResult(std::string st = "", int dur = 0, int cm = 0, int mv = 0) :
		sorttype(st),
		duration(dur),
		cmp(cm),
		moves(mv)
	{
		SetSortType(st);
	}

	//copy constructor of SortResult
	SortResult(const SortResult& other_sortresult) :
		sorttype(other_sortresult.sorttype),
		duration(other_sortresult.duration),
		cmp(other_sortresult.cmp),
		moves(other_sortresult.moves)
	{

	}

	~SortResult()
	{

	}

	std::string sorttype;
	int duration; // sorting time
	int cmp; // the number ofcompare 
	int moves; // the number of moves (or swaps) 

	void SetSortType(std::string& s)
	{
		sorttype = s;
	}
};

class SortStrategy
{
public:
	SortStrategy() {}
	~SortStrategy() {}

	virtual SortResult SortSequence(Sequence &sequence) = 0;
};

class SelectionSort : public SortStrategy
{
public:
	SelectionSort(){}
	~SelectionSort(){}

	const std::string alg_name = "Selection Sort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
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
		return sr;
	}
};

class InsertionSort : public SortStrategy
{
public:

	InsertionSort()	{}
	~InsertionSort(){}

	const std::string alg_name = "Insertion Sort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
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
		return sr;
	}
};

class QuickSort : public SortStrategy
{
public:
	QuickSort(){}
	~QuickSort(){}

	const std::string alg_name = "QuickSort";
	SortResult sr{ alg_name };

	SortResult SortSequence(Sequence &sequence) override
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
			return sr;
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
		int left = 0;
		int right = sequence.fd.size() - 1;
		MergeSequence(sequence, left, right);
		return sr;
	};

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
		return sr;
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

		return sr;
	}

private:

	//determine gaps for h-sorting if 3*N > max of Ì.Ciura’s A102549 sequence
	int defineMoreGaps(int n, int i) const
	{
		int d = 0;
		if (i % 2)
		{
			d = (8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1);
		}
		else
		{
			d = (9 * pow(2, i) - 9 * pow(2, i / 2) + 1);
		}
		return d;
	}

};

class Context
{
protected:
	SortStrategy* sortStrategy;

public:
	Context(){}
	~Context(){}

	virtual SortResult ApplySortStrategy(Sequence &sequence, SortStrategy *sorttype) = 0;
};

//load text data from file, delete punctuation and create vector of words
class FileLoader
{
public:

	FileLoader(){};

	FileLoader(const std::string& path)
	{
		getFileData(path);
	};

	~FileLoader(){};

	std::string data;

	//get string data
	void getFileData(const std::string& path)
	{
		std::ifstream in(path);
		data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());
	}

};

class FileSorter : public Context
{
public:

	FileSorter(){};
	FileSorter(const std::string filepath, bool stable = 1, bool memory = 1, char datatype = 's') :
		filepath(filepath),
		stable(stable),
		memory(memory),
		datatype(datatype),
		sortresults({})
	{
		FileLoader fileObject(filepath);
		Sequence sequence{ fileObject.data, stable, memory, datatype };
		SortFile(sequence, stable, memory, 0);
	}

	~FileSorter(){};

	std::map<std::string, SortStrategy*> strategies;

	std::vector<SortResult> sortresults;

	void SortFile(Sequence &sequence, bool stable = 1, bool memory = 1, bool recommend = 1)
	{
		strategies.insert(std::pair<std::string, SortStrategy*>("ins", new InsertionSort));
		strategies["ins"] = new InsertionSort;
		strategies["qs"] = new QuickSort;
		strategies["shs"] = new ShellSort;
		strategies["hs"] = new HeapSort;
		strategies["ms"] = new MergeSort;
		strategies["sls"] = new SelectionSort;
		std::string recommended;

		if (recommend)
		{
			recommended = RecommendStrategy(sequence, stable, memory);
			sortresults.push_back(ApplySortStrategy(sequence, strategies[recommended]));
		}
		else
		{
			std::map<std::string, SortStrategy*>::iterator it;
			for (it = strategies.begin(); it != strategies.end(); ++it)
			{
				sortresults.push_back(ApplySortStrategy(sequence, (*it).second));
			}
		}

		WriteResult(sortresults, sequence);
	};

private:

	const std::string filepath;
	bool stable;
	bool memory;
	char datatype;

	SortResult ApplySortStrategy(Sequence &sequence, SortStrategy *sorttype) override
	{
		SortResult sr;

		using nanoseconds = std::chrono::duration < float, std::ratio<1, 1000000000> > ;
		std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();

		sr = sorttype->SortSequence(sequence);

		std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

		sr.duration = duration;

		return sr;
	}

	std::string RecommendStrategy(Sequence &sequence, bool stable, bool memory)
	{
		if (sequence.fd.size() < 100)
		{
			return "ins";
		}
		else if (sequence.fd.size() > 100 && sequence.fd.size() < 1000)
		{
			if (stable)
			{
				return "qs";
			}
			else
			{
				return "shs";
			}
		}
		else if (sequence.fd.size() > 1000)
		{
			if (!memory)
			{
				if (stable)
				{
					return "qs";
				}
				else
				{
					return "hs";
				}
			}
			else
			{
				return "ms";
			}
		}
	}

	//void WriteResult(Sequence &sequence)
	void WriteResult(std::vector<SortResult> sortresults, Sequence &sequence)
	{
		for (int i = 0; i < sortresults.size(); ++i)
		{
			std::cout << "sorttype: " << sortresults.at(i).sorttype << std::endl;
			std::cout << "exch number: " << sortresults.at(i).moves << std::endl;
			std::cout << "compare number: " << sortresults.at(i).cmp << std::endl;
			std::cout << "sorttime: " << sortresults.at(i).duration << std::endl << std::endl;
			std::cout << std::endl;
		}

		std::vector<std::string>::iterator cur;
		//std::vector<std::shared_ptr<void>>::iterator cur;
		for (cur = sequence.fd.begin(); cur < sequence.fd.end(); ++cur)
		{
			std::cout << *cur << std::endl;
		}
	}
};

int main(int argc, char* argv[])
{
	FileSorter file("D:/ìîè äîêóìåíòû/visual studio 2013/Projects/SortingAlgorithms/demo.txt");
	_getch();
	return 0;
};