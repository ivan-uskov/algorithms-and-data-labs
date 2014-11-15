#pragma once

class CTreeIO
{

public:

    CTreeIO(char* inputFileName);
    ~CTreeIO();

    bool IsError();
    void PrintError(std::ostream & output);
    bool ReadTree();

private:

    typedef enum class ErrorType
    {
        None,
        OpenInputFile
    };

    ErrorType m_error;
    std::ifstream m_input;

    bool OpenInputFile(char* fileName);

};

