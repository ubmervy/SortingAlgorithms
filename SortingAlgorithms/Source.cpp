#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <vector>

using namespace std;

class SortStrategy
{
public:
	SortStrategy(void){}
	~SortStrategy(void){}

	int duration; // длительность сортировки данных
	int cmp; // количество сравнений
	int exch; // количество обменов

	virtual void SortSequence(vector<string> data) = 0;
};

class SelectionSort : public SortStrategy
{
public:
	SelectionSort(){}
	~SelectionSort(){}

	void SortSequence(vector<string> data){ cout << "SelectionSort" << endl; };
};

class InsertionSort : public SortStrategy
{
public:
	InsertionSort(){}
	~InsertionSort(){}

	void SortSequence(vector<string> data){ cout << "InsertionSort" << endl; };
};

class QuickSort : public SortStrategy
{
public:
	QuickSort(){}
	~QuickSort(){}

	void SortSequence(vector<string> data){ cout << "QuickSort" << endl; };
};

class MergeSort : public SortStrategy
{
public:
	MergeSort(){}
	~MergeSort(){}

	void SortSequence(vector<string> data){ cout << "MergeSort" << endl; };
};

class ShellSort : public SortStrategy
{
public:
	ShellSort(){}
	~ShellSort(){}

	void SortSequence(vector<string> data)
	{ 
		vector<string>::iterator cur;
		for (cur = data.begin(); cur < data.end(); ++cur)
		{
		cout << *cur << endl;  
		}
	};
};

class Context
{
protected:
	SortStrategy* sortStrategy;

public:
	Context(void){}
	~Context(void){}

	virtual void ApplySortStrategy(SortStrategy* v) = 0;
};

class LoadFile
{
public:
	LoadFile(){};

	LoadFile(const string &file)
	{
		string line;
		ifstream myfile(file);
		if (myfile.is_open())
		{
			while (getline(myfile, line, ';'))
			{
				data.push_back(line);
			}
			myfile.close();
		}

	}
	~LoadFile(void){}

	vector<string> data;

};

class FileToSort : public Context, private LoadFile
{
public:

	vector<string> filedata;

	FileToSort(const string &file)
	{
		LoadFile fileObject(file);
		filedata = fileObject.data;
	}

	~FileToSort(void){}

	void SortFile(SortStrategy* sorttype)
	{
		ApplySortStrategy(sorttype);
	}

private:


	void ApplySortStrategy(SortStrategy* sorttype)
	{
		sorttype->SortSequence(filedata);
	}

};

int main()
{
	FileToSort file("demo.txt");

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