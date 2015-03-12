//FileSorter.h
#ifndef FileSorter_h
#define FileSorter_h
#include "Context.h"
#include "FileLoader.h"
#include "Sequence.h"
#include "SortResult.h"
#include "SortStrategy.h"
#include "ListOfSpaces.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

class FileSorter : public Context
{
public:
	//constructor
	FileSorter(std::string &srcpath, std::string &dstpath, bool stable);

	//destructor
	~FileSorter();

	std::map<std::string, std::unique_ptr<SortStrategy>> _strategies; // map of all strategies available

	std::vector<SortResult> _sortresults; // vector of all results available after sorting

	std::string _recommendedStrategy; //recommended sorting algorithm

	//Initiates and manages sorting process
	void SortFile(Sequence &sequence, bool stable, bool memory, bool test);

private:
	std::string _srcpath; // path to input file
	std::string _dstpath; // path to output file
	bool _stable; // stable sorting required sign
	bool _memory; // extra disk memory available for sorting input sequence
	FileLoader _fileObject; // object for serialization

	//Sets context according to given SortStrategy object
	void SetSortStrategy(std::unique_ptr<SortStrategy> &strategy) override;

	//Applies SortSequence method according to current context
	SortResult ApplySortStrategy(Sequence &sequence) override;

	//Analizes which algorithm suits best for sorting input sequence
	std::string RecommendStrategy(Sequence &sequence);

	//Writes results of sorting - to output file and on the screen
	void WriteResult(Sequence &sequence);
};

#endif // !FileSorter_h
