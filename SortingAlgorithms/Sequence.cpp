//Sequence.cpp
#include "Sequence.h";
#include <iostream>;
#include <algorithm>;
#include <sstream>;
#include <locale.h>;
#include <vector>;
#include <memory>;

//constructor
Sequence::Sequence(std::string &data)
{
	CreateSequence(data);
};

//copy constructor
Sequence::Sequence(const Sequence& other_sequence)
{
	fd = other_sequence.fd;
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

////parse file data into vector
void Sequence::CreateSequence(std::string data)
{
	//convert text to lower case
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	//set up and apply locale object
	std::stringstream inputStringStream(data);
	inputStringStream.imbue(std::locale(inputStringStream.getloc(), std::unique_ptr<ListOfSpaces>(new Sequence::ListOfSpaces).release()));

	std::string token;
	while (inputStringStream >> token)
	{
		fd.push_back(token);
	}
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
