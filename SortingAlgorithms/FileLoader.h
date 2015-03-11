//FileLoader.h
#ifndef FileLoader_h
#define FileLoader_h
#include "Sequence.h"
#include <string>

class FileLoader
{
public:
	//constructor
	FileLoader();

	//copy constructor
	FileLoader(FileLoader& other);

	//destructor
	~FileLoader();

	//Gets string of file content
	std::string GetFileData(std::string& srcpath);

	//Write sorted data to file at dstpath
	void WriteToFile(const std::string& dstpath, Sequence& sequence);

	/*CopyFromTo(std::string& srcpath, std::string& dstpath)*/
};

#endif // !FileLoader_h