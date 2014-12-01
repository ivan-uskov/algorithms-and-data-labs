#include "stdafx.h"
#include "WorkAnalizer.h"

using namespace std;


CWorkAnalizer::CWorkAnalizer(istream & input)
    :m_error( Error::None )
{
    string buff;
    getline(input, buff);

    ReadOperations(buff);
    if (IsError())
    {        
        return;
    }

    m_operationsCount = m_operations.size();
    ReadLinks(input);

    size_t endPoint;
    if (!InitEndPoint(endPoint))
    {
        m_error = Error::InvalidGraph;
    }
    else
    {
        InitOperationsWeight(endPoint, 0);
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
    if (!InitStartPoint(startPoint))
    {
        return false;        
    }

    m_availeble.push_back(startPoint);

    while (m_availeble.size() > 0)
    {
        auto newMax = GetMaxAvaileble();
        way.push_back(newMax);
        for (auto id : m_operations[newMax].GetNexts())
        {
            m_availeble.push_back(id);
        }
        DeleteFromAvaileble(newMax);
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

void CWorkAnalizer::DeleteFromAvaileble(size_t id)
{
    auto it = find_if(m_availeble.begin(), m_availeble.end(), [id](size_t i){ return i == id; });
    if (it != m_availeble.end())
    {
        m_availeble.erase(it);
    }
}

size_t CWorkAnalizer::GetMaxAvaileble()const
{
    size_t max = m_availeble.front();

    auto IfMax = [max](size_t i) 
    {
        return i > max;
    };
    auto it = find_if(m_availeble.begin(), m_availeble.end(), IfMax);

    if (it != m_availeble.end())
    {
        max = *it;
    }
    return max;
}

bool CWorkAnalizer::InitStartPoint(size_t & startPoint)
{
    auto IsOperUndependent = [](COperation oper)
    {
        return oper.IsUndependent();
    };
    
    return InitPoint(startPoint, IsOperUndependent);
}

bool CWorkAnalizer::InitEndPoint(size_t & endPoint)
{
    auto IsOperLast = [](COperation oper)
    {
        return oper.IsLast();
    };
  
    return InitPoint(endPoint, IsOperLast);
}

bool CWorkAnalizer::InitPoint(size_t & point, std::function<bool(COperation)> fn)
{
    auto pointIt = find_if(m_operations.begin(), m_operations.end(), fn);
    if (pointIt < m_operations.end())
    {
        point = pointIt - m_operations.begin();
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

void CWorkAnalizer::InitOperationsWeight(size_t id, size_t weight)
{
    COperation * curr = &(m_operations[id]);
    auto newWeight = weight + curr->GetSize();
    auto oldWeight = curr->GetWight();
    if (oldWeight < newWeight)
    {
        curr->SetWight(newWeight);
        oldWeight = newWeight;
    }
    
    auto prevs = curr->GetPrevs();
    for (auto it = prevs.begin(); it != prevs.end(); ++it)
    {
        InitOperationsWeight(*it, oldWeight);
    }
}