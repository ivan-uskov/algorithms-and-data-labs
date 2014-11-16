#include "stdafx.h"
#include "TreeIO.h"

using namespace std;

CTreeIO::CTreeIO(char* inputFileName)
{
    if (!OpenInputFile(inputFileName))
    {
        m_error = ErrorType::OpenInputFile;
    }
}

CTreeIO::~CTreeIO()
{
    m_input.close();
}

/* Public methods */

bool CTreeIO::IsError()const
{
    return !(m_error == ErrorType::None);
}

bool CTreeIO::ReadTree(CTree & tree)
{
    size_t nodeCount;
    if (!ReadNodeCount(nodeCount))
    {
        m_error = ErrorType::ReadNodeCount;
        return false;
    }
    tree.SetNodeCount(nodeCount);

    if (!ReadLinks(tree))
    {
        m_error = ErrorType::ReadLinks;
        return false;
    }
    return true;
}

void CTreeIO::PrintError(std::ostream & output)const
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

void CTreeIO::PrintRoots(ostream & output, vector<size_t> roots)
{
    if (roots.empty())
    {
        output << "Error: has no roots" << endl;
        return;
    }

    output << roots.size() << endl;
    for (size_t root : roots)
    {
        output << root << " ";
    }
    output << endl;
}

/* Private methods */

bool CTreeIO::OpenInputFile(char* fileName)
{
    this->m_input.open(fileName);
    return !this->m_input.bad();
}

bool CTreeIO::ReadNodeCount(size_t & count)
{
    if (m_input.eof())
    {
        return false;
    }

    string str;
    getline(m_input, str);
    istringstream strStrm(str);
    return static_cast<bool>(strStrm >> count);
}

bool CTreeIO::ReadLinks(CTree & tree)
{
    while (m_input.peek() != EOF)
    {
        size_t x, y;
        string str;
        getline(m_input, str);
        istringstream strStrm(str);
        if (!(strStrm >> x >> y))
        {
            return false;
        }
        tree.AddLink(x, y);
    }
    return true;
}