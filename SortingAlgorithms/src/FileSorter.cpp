//FileSorter.cpp
#include "../h/FileSorter.h"
#include "../h/Context.h"
#include "../h/SortResult.h"
#include "../h/SortStrategy.h"
#include "../h/SelectionSortStrategy.h"
#include "../h/InsertionSortStrategy.h"
#include "../h/QuickSortStrategy.h"
#include "../h/MergeSortStrategy.h"
#include "../h/HeapSortStrategy.h"
#include "../h/ShellSortStrategy.h"
#include "../h/Sequence.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale.h>
#include <memory>
#include <stack>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

//constructor
FileSorter::FileSorter(Sequence &sequence, int bound, bool stable, bool recommend) :
_stable(stable),
_recommend(recommend)
{
    SortFile(sequence, bound);
}

//destructor
FileSorter::~FileSorter()
{

}

//performes sorting process
void FileSorter::SortFile(Sequence &sequence, int bound)
{
    _strategies["Heap"] = std::unique_ptr<SortStrategy>(new HeapSortStrategy);
    _strategies["Insertion"] = std::unique_ptr<SortStrategy>(new InsertionSortStrategy);
    _strategies["Merge"] = std::unique_ptr<SortStrategy>(new MergeSortStrategy);
    _strategies["Quick"] = std::unique_ptr<SortStrategy>(new QuickSortStrategy);
    _strategies["Shell"] = std::unique_ptr<SortStrategy>(new ShellSortStrategy);
    _strategies["Selection"] = std::unique_ptr<SortStrategy>(new SelectionSortStrategy);

    //Chooses sort strategy according to given parameters - stability requirement, percent of unique words of input, total umber of words
    if (_recommend)
    {
        _recommendedStrategy = RecommendStrategy(sequence);
        std::unique_ptr<SortStrategy> recommendedStrategy = std::move(_strategies[RecommendStrategy(sequence)]);
        SetSortStrategy(recommendedStrategy);
        _sortresults.push_back(ApplySortStrategy(sequence, bound));
    }
    else
    {

        std::map<std::string, std::unique_ptr<SortStrategy>>::iterator it;
        for (it = _strategies.begin(); it != _strategies.end(); ++it)
        {
            std::unique_ptr<SortStrategy> currentStrategy = std::move((*it).second);
            SetSortStrategy(currentStrategy);
            _sortresults.push_back(ApplySortStrategy(sequence, bound));
        }
    //sorts results by duration
    //std::sort(_sortresults.begin(), _sortresults.end());
    }

}

//Sets context according to given SortStrategy object
void FileSorter::SetSortStrategy(std::unique_ptr<SortStrategy> &strategy)
{
    sortStrategy.reset(nullptr);
    sortStrategy = std::move(strategy);
}

//Applies SortSequence method according to current context
SortResult FileSorter::ApplySortStrategy(Sequence &sequence, int bound)
{
    return sortStrategy->SortSequence(sequence, bound);
}

//Decides which algorithm suits best for sorting input sequence
std::string FileSorter::RecommendStrategy(Sequence &sequence)
{
    if ((sequence.fd.size() < 500) && (sequence._unique_words < 70))
    {
        return "Insertion";
    }
        if ((sequence.fd.size() < 500) && (sequence.fd.size() < 1000) && (sequence._unique_words < 50) && (_stable))
    {
        return "Insertion";
    }
    else if ((sequence.fd.size() >= 500) && (sequence.fd.size() < 1000) && (sequence._unique_words < 70) && (!_stable))
    {
        return "Heap";
    }
    else if (sequence.fd.size() >= 1000 && (_stable))
    {
        return "Merge";
    }
    return "Quick";
}
