//SortResult.h
#ifndef SortResult_h
#define SortResult_h
#include <string>

class SortResult
{
public:
	//constructor
	SortResult(std::string st, double dur = 0.0, int cm = 0, int mv = 0);

	//copy constructor
	SortResult(const SortResult& other_sortresult);

	//destructor
	~SortResult();

	double duration; // sorting time
	std::string sorttype; //sorting algorithm name
	int cmp; // number of compares
	int moves; // number of element's moves (exchanges)
};
#endif // !SortResult_h
