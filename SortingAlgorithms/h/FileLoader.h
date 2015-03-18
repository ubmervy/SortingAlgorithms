//FileLoader.h
#ifndef FileLoader_h
#define FileLoader_h
#include "../h/Sequence.h"
#include "../h/SortResult.h"
#include "../h/FileSorter.h"

class FileLoader
{
public:
    //constructor
    FileLoader();

    //copy constructor
    FileLoader(FileLoader& other);

    //destructor
    ~FileLoader();

    //gets string of file content
    std::string GetFileData(std::string& srcpath);

    //Writes results of sorting to output file
    void WriteSequenceToFile(const std::string& dstpath, Sequence &sequence);

    //writes sorting process statistics to outpit file with "_stat" suffix
    void WriteStatToFile(const std::string& dstpath_stat, Sequence &sequence, FileSorter& filesorter);


    /*
    //copies data from scr to dest
    CopyFromTo(std::string& srcpath, std::string& dstpath)

    //generate randomized input file
    FileLoader::GenerateRandomInput();
    */
};

#endif // !FileLoader_h
