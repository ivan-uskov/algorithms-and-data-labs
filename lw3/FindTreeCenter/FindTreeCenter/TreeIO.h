#pragma once
#include "Tree.h"

class CTreeIO
{

public:

    CTreeIO(char* inputFileName);
    ~CTreeIO();

    bool IsError()const;
    void PrintError(std::ostream & output)const;
    bool ReadTree(CTree & tree);
    void PrintRoots(std::ostream & output, std::vector<size_t> roots);

private:

    typedef enum class ErrorType
    {
        None,
        OpenInputFile,
        ReadNodeCount,
        ReadLinks
    };

    ErrorType m_error;
    std::ifstream m_input;

    bool OpenInputFile(char* fileName);
    bool ReadNodeCount(size_t & count);
    bool ReadLinks(CTree & tree);

};

