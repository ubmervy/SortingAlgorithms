//Sequence.h
#ifndef Sequence_h
#define Sequence_h

#include <string>
#include <vector>

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
	void Sequence::release(Sequence &other_sequence);

	//set up table of delimiters to delete
	struct ListOfSpaces : std::ctype < char >
	{
		Sequence::ListOfSpaces() : std::ctype<char>(DelimsTable())
		{
		}

		static mask const* DelimsTable()
		{
			static mask rc[table_size];
			rc[':'] = std::ctype_base::space;
			rc[';'] = std::ctype_base::space;
			rc[' '] = std::ctype_base::space;
			rc['.'] = std::ctype_base::space;
			rc['-'] = std::ctype_base::space;
			rc['('] = std::ctype_base::space;
			rc[')'] = std::ctype_base::space;
			rc['+'] = std::ctype_base::space;
			rc['/'] = std::ctype_base::space;
			rc['"'] = std::ctype_base::space;
			rc['{'] = std::ctype_base::space;
			rc['}'] = std::ctype_base::space;
			rc['@'] = std::ctype_base::space;
			rc['#'] = std::ctype_base::space;
			rc['$'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['\t'] = std::ctype_base::space;
			rc['\n'] = std::ctype_base::space;
			rc[';'] = std::ctype_base::space;
			rc['~'] = std::ctype_base::space;
			rc['¹'] = std::ctype_base::space;
			rc['%'] = std::ctype_base::space;
			rc['*'] = std::ctype_base::space;
			rc['['] = std::ctype_base::space;
			rc[']'] = std::ctype_base::space;
			rc['='] = std::ctype_base::space;
			rc['“'] = std::ctype_base::space;
			rc['&'] = std::ctype_base::space;
			rc['\''] = std::ctype_base::space;
			rc[','] = std::ctype_base::space;
			rc['<'] = std::ctype_base::space;
			rc['>'] = std::ctype_base::space;
			rc['\\'] = std::ctype_base::space;
			rc['^'] = std::ctype_base::space;
			rc['|'] = std::ctype_base::space;

			return &rc[0];
		}
	};
};

#endif // !Sequence_h
