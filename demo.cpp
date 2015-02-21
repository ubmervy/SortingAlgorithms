#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <iterator>
#include <math.h>
#include <stack>
#include <ctime>
#include <chrono>
#include <string.h>
#include <stdio.h>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;
//using namespace std::chrono;
using std::ostream;
using std::vector;
using std::pair;

int cmp = 0, asgn = 0, exch = 0;
int maxStack;
vector <int> c;

template <class Item>
void swapItems(Item &A, Item &B)
{
	Item t = A; A = B; B = t;
	//exch++;
}

template <class T>
void SelectionSort(T *a, int l, int r)
{
	cout << __FUNCSIG__ << endl;
	for (int i = l; i <= r; i++)
	{
		//cmp++;
		int min = i;
		for (int j = i + 1; j <= r; j++)
		{
			//cmp += 2;
			if (a[j] < a[min]) min = j;
		}
		swapItems(a[i], a[min]);
		/*cout << i << ": ";
		for (int k = 0; k <= r; k++) cout << a[k] << " ";
		cout << endl;*/
	}
}

template <class T>
void ShellSort(T *a, int l, int r)
{
	cout << __FUNCSIG__ << endl;
	int d, i, j;
	defineIterations(2, (r - l - 1));
	d = c.back();

 	while (d < (r - l))
	{
		//cmp++;
		for (i = 0; i < ((r - l) - d); i++)
		{
			//cmp++;
			j = i;
			while (j >= 0 && a[j] > a[j + d])
			{
				//cmp += 2;
				swapItems(a[j], a[j + d]);
				/*cout << "i = " << i << " j = " << j << ": ";
				for (int k = 0; k < (r - l); k++) cout << a[k] << " ";
				cout << endl;*/
				j--;
			}
		}
		d = c.back();
	}
}

void defineIterations(int f, int n)
{
	int cm[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
	switch (f)
	{
	case 1:
		for (int k = 0; k < sizeof(cm) / sizeof(cm[0]) - 1; k += sizeof(cm[0]))
		{
			c[k] = cm[k];
		}
	case 2:
		int d = 0, i = 0;
		if (n % 2)
		{
			d = (8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1);
			while (d <= n)
			{
				c.push_back(d);
				i++;
				d = (8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1);
			}
		}
		else
		{
			d = (9 * pow(2, i) - 9 * pow(2, i / 2) + 1);
			while (d <= n)
			{
				c.push_back(d);
				i++;
				d = (9 * pow(2, i) - 9 * pow(2, i / 2) + 1);
			}
		}
	}
}

void push2(stack <int> &s, int A, int B)
{
	s.push(B);
	s.push(A);
}

template <class T>
void QuickSort(T *a, int l, int r)
{
	cout << __FUNCSIG__ << endl;
	stack <int> s;
	s.push(r);
	s.push(l);
	maxStack = s.size() / 2;

	while (!s.empty())
	{
		l = s.top();
		s.pop();
		r = s.top();
		s.pop();
		if (r <= l)
		{
			//cmp++;
			continue;
		}
		int i = partition(a, l, r);

		//push2(s, l, i - 1);
		//push2(s, i + 1, r);

		//push2(s, i + 1, r);
		//push2(s, l, i - 1);

		if (i - l > r - i)
		{
			//cmp++;
			push2(s, l, i - 1);
			push2(s, i + 1, r);
		}
		else
		{
			push2(s, i + 1, r);
			push2(s, l, i - 1);

		}
		if (s.size() / 2 > (unsigned)maxStack)
		{
			maxStack = s.size() / 2;
			//cmp++;
		}

	}

}

template <class T>
int partition(T *a, int l, int r)
{
	int i = l - 1, j = r; T v = a[r];
	for (;;)
	{
		while (a[++i] < v) { cmp++; };
		while (v < a[--j])
		{
			if (j == l);
			//cmp++;
			break;
		}
		if (i >= j) { //cmp++; 
			break;
		}
		//		else if (i < j && a[i] == v) return j;
		swapItems(a[i], a[j]);
	}
	swapItems(a[i], a[r]);
	return i;
}

template <class T>
void InsertSort(T *a, int l, int r)
{
	cout << __FUNCSIG__ << endl;
	for (int i = l + 1; i <= r; i++)
	{
		int j = i;
		T v = a[j];
		while (j > l && v < a[j - 1])
		{
			//cmp += 2;
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}

template <class T>
void Merge2Sort(T *c, T *a, int N, T *b, int M)
{
	for (int i = 0, j = 0, k = 0; k < N + M; k++)
	{
		/*for (int d = 0; d < N; d++)
		cout << a[d] << " ";
		cout << endl;

		for (int r = 0; r < M; r++)
		cout << b[r] << " ";*/

		if (i == N)
		{
			c[k] = b[j++];
			continue;
		}
		if (j == M)
		{
			c[k] = a[i++];
			continue;
		}
		if (a[i] < b[j])
		{
			cout << a[i] << "(a) ";
			c[k] = a[i++];

		}
		else
		{
			cout << b[j] << "(b) ";
			c[k] = b[j++];
		}
	}

}

template <class T>
void merge(T *a, int l, int m, int r)
{
	int i, j;
	static T aux[13];
	for (i = m + 1; i > l; --i)
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; ++j)
		aux[r + m - j] = a[j + 1];
	for (int k = 0; k < r; ++k)
	{
		if (aux[j] < aux[i])
			a[k] = aux[j--]; else a[k] = aux[i++];
	}
}

//int form_pair(vector<string>::iterator v) { return std::make_pair(v, *v); }

template <class T>
void MergeSort(T *a, int l, int r)
{
	if (r <= l) return;
	int m = (r - l)/2;
	MergeSort (a, l, m);
	MergeSort (a, m+1, r);
	merge (a, l, m, r);
}

//int form_pair(vector<string>::iterator v) { return std::make_pair(v, *v); }

template <class T>
void CountSort(const T &m)
{
	vector<int> vec (m.size());
	vector<string> aux(m.size());
	vector<int> x(m.size());

	for (auto i = vec.begin(); i != vec.end(); ++i)
	{
		auto d = i - vec.begin() - 1;
		if (m.count(d))
			vec[d + 1] = m.count(d);
		//cout << vec[d+1] << " ";
	}

	for (auto i = vec.begin(); i != vec.end() - 1; ++i)
	{
		auto d = i - vec.begin();
		vec[d+1] += vec[d];
	}

	for (auto i = m.begin(); i != m.end(); ++i)

	{
		aux[vec[(*i).first]++] = (*i).second;
	}

	//std::transform(aux.begin(), aux.end(), x.begin(), make_pair());

}

template <class T>
void SortAndPrint(char *a, int l, int r, void(*srt)(T* a, int l, int r))
{
	using nanoseconds = std::chrono::duration < float, std::ratio<1, 1000000000> > ;
	std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();

	srt(a, l, r);

	std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

	printf("%14s %10s %10s\n", "duration", "Exch", "Cmp");
	printf("%14ld %10d %10d\n", duration, exch, cmp);
	//exch = 0;
	//cmp = 0;
}

int main()
{
	//char a[] = "AAEEGILMNOPRSTX";
	char a[] = "XTSRPONMLIGEEAA";
	//char a[] = "ASORTINGEXAMPLE";
	//char a[] = "dweorivgnaeopriwerbnaeorbmdtynpymyombevftineruiyrbfdilbmtyjyumkpmkyokjweriovhtuigbtmtynhumjklpilolkh";
	//char a[] = "AEQSUYEINOST";
	int lenght = sizeof(a) / sizeof(a[0]);

	void(*p[5])(char*, int, int) = { InsertSort, SelectionSort, ShellSort, QuickSort, MergeSort };

	for (int i = 0; i < 5; ++i)
		SortAndPrint(a, 0, lenght - 2, p[i]);

	//MergeSort(a, a, lenght / 2, a + lenght / 2, (int)(lenght - lenght/2));
	//MergeSort2(a, 0, 5, lenght - 2);

	typedef std::multimap<int, string> names;
	names m;

	m.insert(names::value_type(1, "Anderson"));
	m.insert(names::value_type(2, "Jones"));
	m.insert(names::value_type(2, "Moore"));
	m.insert(names::value_type(1, "Wilson"));
	m.insert(names::value_type(2, "Watson"));
	m.insert(names::value_type(2, "Jackson"));
	m.insert(names::value_type(2, "Nickson"));
	
	CountSort(m);

	/*void (*p)(char*[], int, int);
	p = InsertSort;
	SortAndPrint(a, 0, lenght - 2, p);

	//InsertSort(a, 0, lenght - 2);
	for (int i = 0; i < lenght; i++) cout << a[i] << " ";
	cout << endl << endl;

	using nanoseconds = std::chrono::duration < float, std::ratio<1, 1000000000> > ;
	std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
	QuickSort(a, 0, lenght - 2);
	cout << "exch random: " << exch << endl;
	cout << "max stack size random: " << maxStack << endl;
	exch = 0;
	std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	cout << "time: " << duration << endl;
	QuickSort(a, 0, lenght - 2);
	cout << "exch sorted: " << exch << endl;
	cout << "max stack size sorted: " << maxStack << endl;
	exch = 0;

	//reversed
	char b[100];
	int j = lenght - 1;
	for (int i = 0; i < lenght;)
	{
	b[i++] = a[--j];
	}

	QuickSort(b, 0, lenght - 2);
	cout << "exch reversed: " << exch << endl;
	cout << "max stack size reversed: " << maxStack << endl;


	//ShellSort(a, 0, lenght - 1);
	//selectionSort(a, 0, lenght - 1);

	char buffer [500];

	printf("%10s %14s %10s %10s\n", "duration", "maxStack", "Exch", "Cmp");
	printf("%10d %14ld %10d %10d\n", duration, maxStack, exch, cmp);*/

	_getch();
	return 0;
}