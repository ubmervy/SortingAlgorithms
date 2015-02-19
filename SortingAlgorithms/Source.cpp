#include <iostream>
#include <conio.h>
using namespace std;

template<class T>
class SortStrategy
{
public:
	SortStrategy(void){}
	~SortStrategy(void){}

	int duration; // длительность сортировки данных
	int cmp; // количество сравнений
	int exch; // количество обменов

	virtual void use(void) = 0;
};

template<class T>
class SelectionSort : public SortStrategy<T>
{
public:
	SelectionSort(){}
	~SelectionSort(){}

	void use(void){ cout << "SelectionSort" << endl; };
};

template<class T>
class InsertionSort : public SortStrategy<T>
{
public:
	InsertionSort(){}
	~InsertionSort(){}

	void use(void){ cout << "InsertionSort" << endl; };
};

template<class T>
class QuickSort : public SortStrategy<T>
{
public:
	QuickSort(){}
	~QuickSort(){}

	void use(void){ cout << "QuickSort" << endl; };
};

template<class T>
class MergeSort : public SortStrategy<T>
{
public:
	MergeSort(){}
	~MergeSort(){}

	void use(void){ cout << "MergeSort" << endl; };
};

template<class T>
class ShellSort : public SortStrategy<T>
{
public:
	ShellSort(){}
	~ShellSort(){}

	void use(void){ cout << "ShellSort" << endl; };
};

template<class T>
class Context
{
protected:
	SortStrategy<T>* operation;

public:
	Context(void){}
	~Context(void){}

	virtual void UseStrategy(void) = 0;
	virtual void SetStrategy(SortStrategy<T>* v) = 0;
};

template<class T>
class Client : public Context<T>
{
public:
	Client(void){}
	~Client(void){}

	void UseStrategy(void)
	{
		operation->use();
	}

	void SetStrategy(SortStrategy<T>* sorttype)
	{
		operation = sorttype;
	}
};

int main()
{
	Client<int> customClient;
	QuickSort<int> str1;
	MergeSort<int> str2;
	ShellSort<int> str3;
	InsertionSort<int> str4;
	SelectionSort<int> str5;

	customClient.SetStrategy(&str1);
	customClient.UseStrategy();
	customClient.SetStrategy(&str2);
	customClient.UseStrategy();
	customClient.SetStrategy(&str3);
	customClient.UseStrategy();
	customClient.SetStrategy(&str4);
	customClient.UseStrategy();
	customClient.SetStrategy(&str5);
	customClient.UseStrategy();

	_getch();
	return 0;
}