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
    std::string outFilePath = "../bin/sorted.txt";
    bool stable = false;
    bool recommend = false;

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
            else
            {
                std::cout << "Not enough or invalid arguments, please try again.\n";
                //std::this_thread::sleep_for(std::chrono::seconds(10));
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

        //sort sequence
        FileSorter filesorter(sequence, stable, recommend);

        //write sorted sequence to file
        fileObject->WriteSequenceToFile(outFilePath, sequence);

        //write sorting process statistics to file
        unsigned found = outFilePath.find_last_of(".");
        std::string dstpath_stat = outFilePath.substr(0,found) + "_stat.txt";
        fileObject->WriteStatToFile(dstpath_stat, sequence, filesorter);
    }

    return 0;
};
