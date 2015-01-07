#include "stdafx.h"
#include "WorkAnalizer.h"

using namespace std;


CWorkAnalizer::CWorkAnalizer(istream & input)
{
    size_t operationsCount = ReadOperationCount(input);
    ReadOperations(input, operationsCount);

    m_operationsCount = m_operations.size();
    ReadLinks(input);

    size_t endPoint = GetEndPoint();
    InitOperationsWeight(endPoint);
}


CWorkAnalizer::~CWorkAnalizer()
{

}

/* Public methods */

CWorkAnalizer::WorkProcess CWorkAnalizer::GetProcess()
{
    WorkProcess process;
    size_t startPoint = GetStartPoint();
    m_availeble.push_back(startPoint);
    auto timeline = GetTimeLine();

    while (m_availeble.size() > 0)
    {
        auto newMax = GetMaxAvailebles();
        size_t id = newMax.front();

        COperation * currentOp = &m_operations[id];
        const string type(currentOp->GetType());

        currentOp->SetExecutionTime(timeline[type]);
        timeline[type] += currentOp->GetTime();
        process[type].push_back(*currentOp);
        EraseFromAvaileble(id);
        EraseFromChilds(id);

        auto & opers = m_operations;
        for (auto it = timeline.begin(); it != timeline.end(); ++it)
        {
            auto ite = find_if(newMax.begin(), newMax.end(), [it, &opers](size_t item){ return it->first == opers[item].GetType(); });
            if (newMax.end() == ite)
            {
                it->second = timeline[type];
            }
        }

        auto nexts = currentOp->GetNexts();
        copy_if(nexts.begin(), nexts.end(), back_inserter(m_availeble), [&opers](size_t id){ return opers[id].IsUndependent(); });
        m_availeble.unique();
    }
    return process;
}

size_t CWorkAnalizer::ReadOperationCount(istream & input)
{
    string buff;
    getline(input, buff);
    size_t operationsCount;

    if (!(istringstream(buff) >> operationsCount))
    {
        throw exception("Can't read operatons count!");
    }

    return operationsCount;
}

/* Private methods */

void CWorkAnalizer::EraseFromChilds(size_t id)
{
    for (auto elt : m_operations[id].GetNexts())
    {
        m_operations[elt].ErasePrev(id);
    }
}

map<string, size_t> CWorkAnalizer::GetTimeLine()const
{
    map<string, size_t> timeline;
    for (auto operation : m_operations)
    {
        timeline[operation.GetType()] = 0;
    }
    return timeline;
}

void CWorkAnalizer::EraseFromAvaileble(size_t id)
{
    auto it = find_if(m_availeble.begin(), m_availeble.end(), [id](size_t i){ return i == id; });
    if (it != m_availeble.end())
    {
        m_availeble.erase(it);
    }
}

list<size_t> CWorkAnalizer::GetMaxAvailebles()const
{
    list<size_t> max;

    for (auto id : m_availeble)
    {
        auto currAv = m_operations[id];
        bool isTypeExists = false;
        for (auto it = max.begin(); it != max.end(); ++it)
        {
            auto currM = m_operations[*it];
            if (currAv.GetType() == currM.GetType())
            {
                isTypeExists = true;
                if (currAv.GetWight() > currM.GetWight())
                {
                    *it = id;
                }
            }
        }
        if (!isTypeExists)
        {
            max.push_back(id);
        }
    }
    max.sort();

    return max;
}

size_t CWorkAnalizer::GetStartPoint()
{
    auto IsOperUndependent = [](COperation oper)
    {
        return oper.IsUndependent();
    };
    
    return GetPoint(IsOperUndependent);
}

size_t CWorkAnalizer::GetEndPoint()
{
    auto IsOperLast = [](COperation oper)
    {
        return oper.IsLast();
    };

    return GetPoint(IsOperLast);
}

size_t CWorkAnalizer::GetPoint(std::function<bool(COperation)> fn)
{
    auto pointIt = find_if(m_operations.begin(), m_operations.end(), fn);
    if (pointIt == m_operations.end())
    {
        throw exception("Cant init border point");
    }

    return pointIt - m_operations.begin();
}

void CWorkAnalizer::ReadOperations(istream & input, size_t operationsCount)
{
    string buff;
    while (operationsCount-- > 0)
    {
        getline(input, buff);
        ReadOperation(buff);
    }

    if (m_operations.empty())
    {
        throw exception("Has no operations!");
    }
}

void CWorkAnalizer::ReadOperation(std::string const& operationStr)
{
    size_t id, size;
    string type;

    if (!(istringstream(operationStr) >> id >> size >> type))
    {
        throw exception(("Error parse operation: " + operationStr).c_str());
    }

    m_operations.push_back(COperation(id, size, type));
}

void CWorkAnalizer::ReadLinks(istream & input)
{
    string buff;
    while (input.peek() != EOF)
    {
        getline(input, buff);
        ReadLink(buff);
    }
}

void CWorkAnalizer::ReadLink(std::string const& linkString)
{
    size_t from, to;

    try
    {
        if (!(istringstream(linkString) >> from >> to))
        {
            throw exception("");
        }

        size_t fromId = GetOperationById(from);
        size_t toId = GetOperationById(to);
        m_operations[fromId].AddNext(toId);
        m_operations[toId].AddPrev(fromId);
    }
    catch (exception const& e)
    {
        throw exception(("Error parse link: " + linkString).c_str());
    }
}

size_t CWorkAnalizer::GetOperationById(size_t id)
{
    auto it = find_if(m_operations.begin(), m_operations.end(), [id](COperation & oper){
        return (oper.GetId() == id);
    });

    if (it == m_operations.end())
    {
        throw exception("");
    }
    return it - m_operations.begin();
}

void CWorkAnalizer::InitOperationsWeight(size_t id, size_t weight)
{
    COperation * curr = &(m_operations[id]);
    auto oldWeight = curr->GetWight();
    auto newWeight = weight + curr->GetTime();

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