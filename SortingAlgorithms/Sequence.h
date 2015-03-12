//Sequence.h
#ifndef Sequence_h
#define Sequence_h

#include <string>
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include "ListOfSpaces.h"

class Sequence
{
public:
	//constructor
	Sequence(std::string &data);

	//copy constructor
	Sequence(const Sequence& other_sequence);

	//move constructor
	Sequence(Sequence&& other_sequence);

	//Destructor
	~Sequence();

	//operator = for copying data from assigned object 
	//Sequence operator=(Sequence&& other_sequence);

	//sequence of file elements
	std::vector<std::string> fd;
private:
	//parse file data into vector
	void CreateSequence(std::string data);

	//swap method for move constructor
	void swap(Sequence &other_sequence) throw ();

	//release vector of elements
	void release(Sequence &other_sequence);
};


#endif // !Sequence_h
