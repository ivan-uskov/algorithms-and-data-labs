#include "stdafx.h"
#include "WorkAnalizer.h"

using namespace std;


CWorkAnalizer::CWorkAnalizer(istream & input)
    :m_error( Error::None )
{
    string buff;
    getline(input, buff);

    ReadOperations(buff);
    if (!IsError())
    {
        m_operationsCount = m_operations.size();
        ReadLinks(input);
    }
}


CWorkAnalizer::~CWorkAnalizer()
{

}

/* Public methods */

bool CWorkAnalizer::GetWay(std::vector<size_t> & way)
{
    way.clear();
    size_t startPoint;
    if (InitStartPoint(startPoint))
    {
        way.push_back(startPoint);
        for (auto id : m_operations[startPoint].GetNexts())
        {
            m_availeble.Insert(id);
        }
    }
    while (m_availeble.Size() > 0)
    {

    }
    return true;
}

void CWorkAnalizer::PrintError()const
{
    switch (m_error)
    {
        case Error::ParseLinks:
        {
            cout << "Error in parse links" << endl;
            break;
        }
        case Error::ParseOperationSizes:
        {
            cout << "Error in parse sizes" << endl;
            break;
        }
        case Error::InvalidGraph:
        {
            cout << "Invalid graph" << endl;
            break;
        }
    }
}

bool CWorkAnalizer::IsError()const
{
    return m_error != Error::None;
}

/* Private methods */

bool CWorkAnalizer::InitStartPoint(size_t & startPoint)
{
    auto IsOperUndependent = [](COperation oper){
        return oper.IsUndependent();
    };
    auto startPointIt = find_if(m_operations.begin(), m_operations.end(), IsOperUndependent);

    if (startPointIt < m_operations.end())
    {
        startPoint = startPointIt - m_operations.begin();
        return true;
    }

    return false;    
}

bool CWorkAnalizer::ReadOperations(string const& operationsSizes)
{
    istringstream operationStrm(operationsSizes);
    size_t size;
    while (operationStrm >> size)
    {
        m_operations.push_back(COperation(size));
    }

    if (m_operations.empty())
    {
        m_error = Error::ParseOperationSizes;
        return false;
    }
    return true;
}

bool CWorkAnalizer::ReadLinks(istream & input)
{
    string buff;
    while (input.peek() != EOF)
    {
        getline(input, buff);
        if (!ReadLink(buff))
        {
            m_error = Error::ParseLinks;
            return false;
        }
    }
    return true;
}

bool CWorkAnalizer::ReadLink(std::string const& linkString)
{
    size_t from, to;
    istringstream linkStrm(linkString);
    if (linkStrm >> from >> to && from < m_operationsCount && to < m_operationsCount)
    {
        m_operations[from].AddNext(to);
        m_operations[to].AddPrev(from);
        return true;
    }
    return false;
}