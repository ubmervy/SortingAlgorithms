//ListOfSpaces.h
#ifndef	ListOfSpaces_h
#define	ListOfSpaces_h
#include <ctype.h>
#include <locale>

namespace ListOfSpaces_NS
{

//set up table of delimiters to delete
struct ListOfSpaces : std::ctype < char >
{
    ListOfSpaces() : std::ctype<char>(DelimsTable())
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
        rc['%'] = std::ctype_base::space;
        rc['*'] = std::ctype_base::space;
        rc['['] = std::ctype_base::space;
        rc[']'] = std::ctype_base::space;
        rc['='] = std::ctype_base::space;
        rc['!'] = std::ctype_base::space;
        rc['?'] = std::ctype_base::space;
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

}

#endif // !ListOfSpaces.h
