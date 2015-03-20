### SortingAlgorithms

Finds sorting algorithm which best suits to sort a given text file. Some test are made to evaluate the effectiveness of 6 most popular sorting algorithms in sorting text files of sizes 100, 500, 1000, and 5000 words for random, reverse and sorted content. Also some tests are made for texts with high percent of duplicated words.

Usage:
Sort file and get full result (6 sorting algorithm): ./sortalgs -in <input file path> (-o <output file path>) 
Sort file with auto-recommended algorithm: ./sortalgs -in <input file path> (-o <output file path>)-r (-s - if stable sort is required)
Test new text files in 100-500-1000-5000 mode: ./sortalgs -in <input file path> (-o <output file path>) -test

GNU GCC compiler version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
Thread model: posix

