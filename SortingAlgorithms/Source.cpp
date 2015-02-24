#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <memory>

class SortStrategy
{
public:
	SortStrategy(void){}
	~SortStrategy(void){}

	int duration; // длительность сортировки данных
	int cmp; // количество сравнений
	int exch; // количество обменов

	virtual void SortSequence(std::vector<std::string> data) = 0;
};

class SelectionSort : public SortStrategy
{
public:
	SelectionSort(){}
	~SelectionSort(){}

	void SortSequence(std::vector<std::string> data){ std::cout << "SelectionSort" << std::endl; };
};

class InsertionSort : public SortStrategy
{
public:
	InsertionSort(){}
	~InsertionSort(){}

	void SortSequence(std::vector<std::string> data){ std::cout << "InsertionSort" << std::endl; };
};

class QuickSort : public SortStrategy
{
public:
	QuickSort(){}
	~QuickSort(){}

	void SortSequence(std::vector<std::string> data){ std::cout << "QuickSort" << std::endl; };
};

class MergeSort : public SortStrategy
{
public:
	MergeSort(){}
	~MergeSort(){}

	void SortSequence(std::vector<std::string> data){ std::cout << "MergeSort" << std::endl; };
};

class ShellSort : public SortStrategy
{
public:
	ShellSort(){}
	~ShellSort(){}

	void SortSequence(std::vector<std::string> data)
	{ 
		std::vector<std::string>::iterator cur;
		for (cur = data.begin(); cur < data.end(); ++cur)
		{
		std::cout << *cur << std::endl;  
		}
	};
};

//abstract class for determing interface 
class Context
{
protected:
	SortStrategy* sortStrategy;

public:
	Context(void){}
	~Context(void){}

	virtual void ApplySortStrategy(SortStrategy* v) = 0;
};

//load text data from file, deleting punctuation and creating vector of words
class LoadFile
{
public:

	LoadFile(const std::string& path)
	{
		sequence = getSequence(path);
	};

	~LoadFile(void){};

	std::vector<std::string> sequence;

private:

	//set up table of delimiters to delete
	struct ListOfSpaces : std::ctype<char>
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
			rc['1'] = std::ctype_base::space;
			rc['2'] = std::ctype_base::space;
			rc['3'] = std::ctype_base::space;
			rc['4'] = std::ctype_base::space;
			rc['5'] = std::ctype_base::space;
			rc['6'] = std::ctype_base::space;
			rc['7'] = std::ctype_base::space;
			rc['8'] = std::ctype_base::space;
			rc['9'] = std::ctype_base::space;
			rc['0'] = std::ctype_base::space;
			rc['@'] = std::ctype_base::space;
			rc['#'] = std::ctype_base::space;
			rc['$'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['\t'] = std::ctype_base::space;
			rc['\n'] = std::ctype_base::space;
			rc[';'] = std::ctype_base::space;
			rc['~'] = std::ctype_base::space;
			rc['є'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['*'] = std::ctype_base::space;
			rc['['] = std::ctype_base::space;
			rc[']'] = std::ctype_base::space;
			rc['='] = std::ctype_base::space;
			rc['У'] = std::ctype_base::space;
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

	//get vector of strings from file
	std::vector<std::string> getSequence(const std::string& path)
	{
		std::vector<std::string> tokens;

		//load file data
		std::ifstream in(path);
		std::string data; 
		data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());
		
		//convert text to lower case
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);

		//set up locale object
		std::stringstream inputStringStream(data);
		inputStringStream.imbue(std::locale(inputStringStream.getloc(), std::unique_ptr<ListOfSpaces>(new ListOfSpaces).release()));

		//fill vector with tokens
		while (inputStringStream)
		{
			std::string token;
			inputStringStream >> token;
			tokens.push_back(token);
		}

		return tokens;
	}

};

class FileToSort : public Context
{
public:

	FileToSort(const std::string& filepath)
	{
		LoadFile fileObject(filepath);
		filedata = fileObject.sequence;
	}

	~FileToSort(void){}

	void SortFile(SortStrategy* sorttype)
	{
		ApplySortStrategy(sorttype);
	}

	std::vector<std::string> filedata;

private:


	void ApplySortStrategy(SortStrategy* sorttype)
	{
		sorttype->SortSequence(filedata);
	}

};

int main()
{
	FileToSort file("D:/мои документы/visual studio 2013/Projects/SortingAlgorithms/demo.txt");

	QuickSort str1;
	MergeSort str2;
	ShellSort str3;
	InsertionSort str4;
	SelectionSort str5;

	file.SortFile(&str1);
	file.SortFile(&str2);
	file.SortFile(&str3);
	file.SortFile(&str4);
	file.SortFile(&str5);

	_getch();
	return 0;
}