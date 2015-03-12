#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
//#include <conio.h>
//#include <ncurses.h>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include <memory>
#include <stack>
#include <chrono>
//#include <thread>
#include <cstring>
#include <ctype.h>

#include "Sequence.h"
#include "SortResult.h"
#include "SortStrategy.h"
#include "SelectionSortStrategy.h"
#include "InsertionSortStrategy.h"
#include "QuickSortStrategy.h"
#include "MergeSortStrategy.h"
#include "HeapSortStrategy.h"
#include "ShellSortStrategy.h"
#include "Context.h"
#include "FileLoader.h"
#include "FileSorter.h"
#include "ListOfSpaces.h"

int main(int argc, char* argv[])
{
	std::string inFilePath;
	std::string outFilePath = "sorted";

	if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is\n -in <input file path> \n -o <output file name> (or it will be saved in sorted.txt)\n -s <stable sorting is required> "; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	}
	else
	{ // if we've got enough parameters
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
			else {
				std::cout << "Not enough or invalid arguments, please try again.\n";
				//std::this_thread::sleep_for(std::chrono::seconds(10));
				exit(0);
			}
		}
	}

	if (inFilePath == "" | outFilePath == "")
	{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Please, enter path to input file with -in option. \n"; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	}
	else
	{
		FileSorter file(inFilePath, outFilePath, false);
	}

	//_getch();
//CURSgetch();
	return 0;
};
