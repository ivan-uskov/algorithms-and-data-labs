#include "stdafx.h"
#include "TreeIO.h"

CTreeIO::CTreeIO(char* inputFileName)
{
    if (!OpenInputFile(inputFileName))
    {
        m_error = ErrorType::OpenInputFile;
    }
}

CTreeIO::~CTreeIO()
{

}

/* Public methods */

bool CTreeIO::IsError()
{
    return !(m_error == ErrorType::None);
}

bool CTreeIO::ReadTree()
{
    char ch;
    while (!m_input.eof())
    {
        m_input >> ch;
        std::cout << ch;
    }
    return true;
}

void CTreeIO::PrintError(std::ostream & output)
{
    switch (m_error)
    {
    case ErrorType::None:
    {
        output << "In input output all right!" << std::endl;
        break;
    }
    case ErrorType::OpenInputFile:
    {
        output << "Can't open input file!" << std::endl;
        break;
    }
    }
}

/* Private methods */

bool CTreeIO::OpenInputFile(char* fileName)
{
    this->m_input.open(fileName);
    return !this->m_input.bad();
}