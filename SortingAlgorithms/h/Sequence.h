//Sequence.h
#ifndef Sequence_h
#define Sequence_h

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <ctype.h>
#include "../h/ListOfSpaces.h"

class Sequence
{
public:
    //constructor
    Sequence(std::string &data);

    //copy constructor
    Sequence(const Sequence& other_sequence);

    //move constructor
    Sequence(Sequence&& other_sequence);

    //destructor
    ~Sequence();

    //operator = for copying data from assigned object
    //Sequence operator=(Sequence&& other_sequence);

    std::vector<std::string> fd; //sequence of file elements

    std::map<std::string, int> fd_unique; //sequence of file unique elements

    int _unique_words; //percent of unique words in input sequence


private:
    //parse file data into vector
    void CreateSequence(std::string data);

    //calculates percent of unique words in a sequence
    int GetUniqueWords();

    //swap method for move constructor
    void swap(Sequence &other_sequence) throw ();

    //release vector of elements
    void release(Sequence &other_sequence);
};


#endif // !Sequence_h
