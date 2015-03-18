//FileLoader.cpp
#include "../h/FileLoader.h"
#include "../h/Sequence.h"
#include <iostream>
#include <fstream>
#include <string>

//constructor
FileLoader::FileLoader()
{

}

//copy constructor
FileLoader::FileLoader(FileLoader& other)
{

}

//destructor
FileLoader::~FileLoader()
{

}

//gets string of file content
std::string FileLoader::GetFileData(std::string& srcpath)
{
    std::string data;
    std::ifstream in(srcpath, std::ios::in);
    data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());
    return data;
}

//Writes results of sorting to output file
void FileLoader::WriteSequenceToFile(const std::string& dstpath, Sequence &sequence)
{
    //write sorted data to file at dstpath
    std::ofstream outseq(dstpath);
    if (outseq.is_open())
    {
        std::vector<std::string>::iterator it;
        for (it = sequence.fd.begin(); it != sequence.fd.end(); ++it)
        {
            outseq << *it << std::endl;
        }
        outseq.close();
    }
}

//writes sorting process statistics to outpit file with "_stat" suffix
void FileLoader::WriteStatToFile(const std::string& dstpath_stat, Sequence &sequence, FileSorter& filesorter)
{
    std::ofstream outstat(dstpath_stat);
    if (outstat.is_open())
    {
        outstat << "Words number: " << sequence.fd.size() << std::endl;
        outstat << "Unique words: " << sequence._unique_words << "%" << std::endl << std::endl;
        if (filesorter._stable) outstat << "Stable sorting was required" << std::endl;
        if (filesorter._recommend) outstat << "Applied sorting algorithm: " << filesorter._recommendedStrategy << std::endl << std::endl;

        outstat << "Duration: " << std::endl;
        for (unsigned int i = 0; i < filesorter._sortresults.size(); ++i)
        {
            outstat << filesorter._sortresults.at(i)._sorttype << " Sort: "<< filesorter._sortresults.at(i)._duration << " sec" << std::endl;
        }
        outstat << std::endl;
        outstat << "Compares: " << std::endl;
        for (unsigned int i = 0; i < filesorter._sortresults.size(); ++i)
        {
            outstat << filesorter._sortresults.at(i)._sorttype << " Sort: "<< filesorter._sortresults.at(i)._cmp << std::endl;
        }
        outstat << std::endl;
        outstat << "Moves (exchanges): " << std::endl;
        for (unsigned int i = 0; i < filesorter._sortresults.size(); ++i)
        {
            outstat << filesorter._sortresults.at(i)._sorttype << " Sort: "<< filesorter._sortresults.at(i)._moves << std::endl;
        }
        outstat.close();
    }
}

/*
FileLoader::CopyFromTo(std::string& srcpath, std::string& dstpath)
{
std::ifstream source(srcpath, std::ios::binary);
std::ofstream dest(dstpath, std::ios::binary);

// file size
source.seekg(0, std::ios::end);
std::ifstream::pos_type size = source.tellg();
source.seekg(0);
// allocate memory for buffer
char* buffer = new char[size];

// copy file
source.read(buffer, size);
dest.write(buffer, size);

// clean up
delete[] buffer;
source.close();
dest.close();
}
*/

/*
   //generate randomized input file
FileLoader::GenerateRandomInput()
{
        srand(time(NULL));
        std::string randnumbers, randnum;

        for (int i = 0; i < 10000; ++i)
        {
            randnumbers.append((std::to_string(rand() % 100000))+ ' ');
        }

        std::stringstream ss(randnumbers);
        ss.imbue(std::locale(ss.getloc(), std::unique_ptr<ListOfSpaces_NS::ListOfSpaces>(new ListOfSpaces_NS::ListOfSpaces()).release()));

        std::ofstream output;
        output.open("/home/ubuntu14/SortingAlgorithms/input_random.txt", std::ofstream::out);
        std::string token;
        int i = 0;
        while (ss >> token)
        {
            output << token << '\n';
            ++i;
        }

        output.close();
}
*/
