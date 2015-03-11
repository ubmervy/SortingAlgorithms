//SelectionSortStrategy.h
#ifndef SelectionSortStrategy_h
#define SelectionSortStrategy_h
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"

class SelectionSortStrategy : public SortStrategy
{
public:
	//constructor
	SelectionSortStrategy();

	//destructor
	~SelectionSortStrategy();

	SortResult	SortSequence(Sequence &sequence) override;

	const std::string alg_name = "Selection Sort";
	SortResult sr{ alg_name };

private:
	void SelectionSortSequence(Sequence &sequence);
};
#endif // !SelectionSortStrategy_h
