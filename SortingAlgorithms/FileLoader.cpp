//FileLoader.cpp
/*Loads text data from input file and writes sorted sequence to destination file*/
#include "FileLoader.h"
#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <string>

//constructor
FileLoader::FileLoader()
{

}

//copy constructor
FileLoader::FileLoader(FileLoader& other)
{

}

//destructor
FileLoader::~FileLoader()
{

}

//Gets string of file content
std::string FileLoader::GetFileData(std::string& srcpath)
{
    std::string data;
    std::ifstream in(srcpath, std::ios::in);
    data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());
    return data;
}

//Write sorted data to file at dstpath
void FileLoader::WriteToFile(const std::string& dstpath, Sequence& sequence)
{
    std::ofstream out(dstpath);
    if (out.is_open())
    {
        std::vector<std::string>::iterator it;
        for (it = sequence.fd.begin(); it != sequence.fd.end(); ++it)
        {
            out << *it << std::endl;
        }
        out.close();
    }
}

/*
FileLoader::CopyFromTo(std::string& srcpath, std::string& dstpath)
{
std::ifstream source(srcpath, std::ios::binary);
std::ofstream dest(dstpath, std::ios::binary);

// file size
source.seekg(0, std::ios::end);
std::ifstream::pos_type size = source.tellg();
source.seekg(0);
// allocate memory for buffer
char* buffer = new char[size];

// copy file
source.read(buffer, size);
dest.write(buffer, size);

// clean up
delete[] buffer;
source.close();
dest.close();
}
*/
