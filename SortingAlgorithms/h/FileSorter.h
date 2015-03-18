//FileSorter.h
#ifndef FileSorter_h
#define FileSorter_h
#include "../h/Context.h"
#include "../h/Sequence.h"
#include "../h/SortResult.h"
#include "../h/SortStrategy.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

class FileSorter : public Context
{
public:
    //constructor
    FileSorter(Sequence& sequence, bool stable, bool recommend);

    //destructor
    ~FileSorter();

    std::map<std::string, std::unique_ptr<SortStrategy>> _strategies; // map of all sortings algorithms available
    std::vector<SortResult> _sortresults; // vector of all results available after sorting
    std::string _recommendedStrategy; //recommended sorting algorithm
    bool _stable; // stable sorting required sign
    bool _recommend; // auto sort algorithm selection sign

    //performes sorting process
    void SortFile(Sequence &sequence);

private:

    //Sets context according to given SortStrategy object
    void SetSortStrategy(std::unique_ptr<SortStrategy> &strategy) override;

    //Applies SortSequence method according to current context
    SortResult ApplySortStrategy(Sequence &sequence) override;

    //Analizes which algorithm suits best for sorting input sequence
    std::string RecommendStrategy(Sequence &sequence);

};

#endif // !FileSorter_h
