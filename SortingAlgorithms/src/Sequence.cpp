//Sequence.cpp
#include "../h/Sequence.h"
#include "../h/ListOfSpaces.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <locale>
#include <vector>
#include <map>
#include <memory>
#include <ctype.h>

//constructor
Sequence::Sequence(std::string &data)
{
    CreateSequence(data);
    _unique_words = GetUniqueWords();
};

//copy constructor
Sequence::Sequence(const Sequence& other_sequence)
{
    fd = other_sequence.fd;
    fd_unique = other_sequence.fd_unique;
    _unique_words = other_sequence._unique_words;
}

// move constructor of Sequence
Sequence::Sequence(Sequence&& other_sequence)
{
    swap(other_sequence);
    release(other_sequence);
}

//Destructor
Sequence::~Sequence()
{
    release(*this);
}

//operator = for copying data from assigned object
/*
Sequence Sequence::operator=(Sequence&& other_sequence)
{
	if (this != &other_sequence)
	{
		release(*this);
		swap(other_sequence);
		release(other_sequence);
	}

	return *this;
}*/

//parse file data into vector
void Sequence::CreateSequence(std::string data)
{
    //convert text to lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    //set up and apply locale object
    std::stringstream inputStringStream(data);
    inputStringStream.imbue(std::locale(inputStringStream.getloc(), std::unique_ptr<ListOfSpaces_NS::ListOfSpaces>(new ListOfSpaces_NS::ListOfSpaces()).release()));

    std::string token;
    int i = 0;
    while (inputStringStream >> token)
    {
        fd.push_back(token);
        fd_unique[token] = i;
        ++i;
    }
}

//calculates percent of unique words in a sequence
int Sequence::GetUniqueWords()
{
    double a = fd_unique.size();
    double b = fd.size();
    auto percent = a/b*100.0;
    return (int)percent;
}

//swap method for move constructor
void Sequence::swap(Sequence &other_sequence) throw ()
{
    std::swap(this->fd, other_sequence.fd);
}

//release vector of elements
void Sequence::release(Sequence &other_sequence)
{
    other_sequence.fd.clear();
    other_sequence.fd.shrink_to_fit();
}

