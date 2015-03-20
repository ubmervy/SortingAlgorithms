#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include <memory>
#include <stack>
#include <chrono>
#include <cstring>
#include <ctype.h>
#include <iomanip>
#include "../h/Context.h"
#include "../h/FileLoader.h"
#include "../h/FileSorter.h"
#include "../h/SortResult.h"
#include "../h/SortStrategy.h"
#include "../h/SelectionSortStrategy.h"
#include "../h/InsertionSortStrategy.h"
#include "../h/QuickSortStrategy.h"
#include "../h/MergeSortStrategy.h"
#include "../h/HeapSortStrategy.h"
#include "../h/ShellSortStrategy.h"

int main(int argc, char* argv[])
{

    std::string inFilePath;
    std::string outFilePath = "sorted.txt";
    bool stable = false;
    bool recommend = false;
    bool test = false;

    if (argc < 3)   // Check the value of argc. If not enough parameters have been passed, inform user and exit.
    {
        std::cout << "Usage is\n -in <input file path> \n -o <output file name> (or it will be saved in sorted.txt)\n -s <stable sorting is required> "; // Inform the user of how to use the program
        std::cin.get();
        exit(0);
    }
    else
    {
        // if we've got enough parameters
        for (int i = 1; i < argc; ++i)
        {
            if (std::string(argv[i]) == "-in")
            {
                inFilePath = std::string(argv[i + 1]);
                ++i;
            }
            else if (std::string(argv[i]) == "-o")
            {
                outFilePath = std::string(argv[i + 1]);
                ++i;
            }
            else if (std::string(argv[i]) == "-s")
            {
                stable = true;
            }
            else if (std::string(argv[i]) == "-r")
            {
                recommend = true;
            }
            else if (std::string(argv[i]) == "-test")
            {
                test = true;
            }
            else
            {
                std::cout << "Not enough or invalid arguments, please try again.\n";
                exit(0);
            }
        }
    }

    if ((inFilePath == "") | (outFilePath == ""))
    {
        // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Please, enter path to input file with -in option. \n"; // Inform the user of how to use the program
        std::cin.get();
        exit(0);
    }
    else
    {
        //create sequence of words from file
        FileLoader* fileObject = new FileLoader();
        std::string filedata = fileObject->GetFileData(inFilePath);
        Sequence sequence { filedata };

        if(test)
        {
            int bound, bound_key;
            const unsigned int sizes[] = {100, 500, 1000, 5000, 10000};

            //find bound closest to sequence size
            for (int i = 0; i < sizeof(sizes)/sizeof(int); ++i)
            {
                //sort sequence
                if (sequence.fd.size() >= sizes[i])
                {
                    bound = sizes[i];
                    bound_key = i;
                    continue;
                }
                else break;
            }

            //get sortresults for each sequence intervals from sizes (up to bound)
            std::map<unsigned int, std::vector<SortResult>> sortresults;
            for (int i = 0; i < bound_key+1; ++i)
            {
                FileSorter filesorter(sequence, sizes[i], stable, recommend);
                std::vector<SortResult> res (filesorter._sortresults.begin(),filesorter._sortresults.end());
                sortresults[sizes[i]] = res;

            //write sorting process statistics to file
//            unsigned found = inFilePath.find_last_of(".");
//            std::string dstpath_stat = inFilePath.substr(0,found) + "_stat" + std::to_string(i) + ".txt";
//            fileObject->WriteStatToFile(dstpath_stat, sequence, filesorter);
            }


            //write sorting process statistics to file
            unsigned found = inFilePath.find_last_of(".");
            std::string dstpath_test = inFilePath.substr(0,found) + "_test.txt";
            //fileObject->WriteStatToFile(dstpath_test, sequence, filesorter);

            //write sorted sequence to file
            std::map<unsigned int, std::vector<SortResult>>::reverse_iterator it_map;
            std::map<unsigned int, std::vector<SortResult>>::reverse_iterator it_map2;
           // std::vector<SortResult>::reverse_iterator it_vec;

            std::ofstream outtest(dstpath_test);
            if (outtest.is_open())
            {
                // Duration
                outtest << "Duration" << std::endl;
                outtest << std::setfill(' ');
                outtest << std::setw(11) << ' '  << '\t';
                for (it_map = sortresults.rbegin(); it_map != sortresults.rend(); ++it_map)
                {
                    outtest << std::setw(10) << std::left << "size = " << (*it_map).first << '\t';
                }
                outtest << std::endl;

                for (int v = 0; v < sortresults[100].size() ; ++v)
                {
                    outtest << std::setw(10) << std::right << sortresults[100].at(v)._sorttype  << '\t';

                    for (it_map2 = sortresults.rbegin(); it_map2 != sortresults.rend(); ++it_map2)
                    {
                        outtest << std::setw(12) << std::left << sortresults[(*it_map2).first].at(v)._duration << '\t';
                    }
                    outtest << std::endl;
                }
                outtest << std::endl;

                // Cmp
                outtest << "Compares" << std::endl;
                outtest << std::setfill(' ');
                outtest << std::setw(11) << ' '  << '\t';
                for (it_map = sortresults.rbegin(); it_map != sortresults.rend(); ++it_map)
                {
                    outtest << std::setw(10) << std::left << "size = " << (*it_map).first << '\t';
                }
                outtest << std::endl;

                for (int v = 0; v < sortresults[100].size() ; ++v)
                {
                    outtest << std::setw(10) << std::right << sortresults[100].at(v)._sorttype << '\t';

                    for (it_map2 = sortresults.rbegin(); it_map2 != sortresults.rend(); ++it_map2)
                    {
                        outtest << std::setw(12) << std::left << sortresults[(*it_map2).first].at(v)._cmp << '\t';
                    }
                    outtest << std::endl;
                }
                outtest << std::endl;

                // Moves (exchanges)
                outtest << "Moves (exchanges)" << std::endl;
                outtest << std::setfill(' ');
                outtest << std::setw(11) << ' '  << '\t';
                for (it_map = sortresults.rbegin(); it_map != sortresults.rend(); ++it_map)
                {
                    outtest << std::setw(10) << std::left << "size = " << (*it_map).first << '\t';
                }
                outtest << std::endl;

                for (int v = 0; v < sortresults[100].size() ; ++v)
                {
                    outtest << std::setw(10) << std::right << sortresults[100].at(v)._sorttype << '\t';

                    for (it_map2 = sortresults.rbegin(); it_map2 != sortresults.rend(); ++it_map2)
                    {
                        outtest << std::setw(12) << std::left << sortresults[(*it_map2).first].at(v)._moves << '\t';
                    }
                    outtest << std::endl;
                }

                outtest.close();
            }

        }

        //working mode (not test)
        else
        {
            //sort sequence
            FileSorter filesorter(sequence, sequence.fd.size(), stable, recommend);

            //write sorted sequence to file
            fileObject->WriteSequenceToFile(outFilePath, sequence);

            //write sorting process statistics to file
            unsigned found = outFilePath.find_last_of(".");
            std::string dstpath_stat = outFilePath.substr(0,found) + "_stat.txt";
            fileObject->WriteStatToFile(dstpath_stat, sequence, filesorter);
        }
    }

    return 0;
};
