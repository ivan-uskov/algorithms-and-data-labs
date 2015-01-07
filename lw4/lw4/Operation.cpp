#include "stdafx.h"
#include "Operation.h"

using namespace std;

COperation::COperation(size_t id, size_t size, string type)
    : m_id( id )
    , m_time( size )
    , m_type( type )
    , m_weight( 0 )
    , m_start( 0 )
    , m_end( 0 )
{
}


COperation::~COperation()
{
}

/* Public methods */

void COperation::ErasePrev(size_t id)
{
    auto it = find_if(m_prevs.begin(), m_prevs.end(), [id](size_t elt){ return elt == id; });
    if (it != m_prevs.end())
    {
        m_prevs.erase(it);
    }
}

void COperation::SetWight(size_t weight)
{
    m_weight = weight;
}

void COperation::SetExecutionTime(size_t start)
{
    m_start = start;
    m_end = start + m_time;
}

size_t COperation::GetStart()const
{
    return m_start;
}

size_t COperation::GetEnd()const
{
    return m_end;
}

size_t COperation::GetId()const
{
    return m_id;
}

size_t COperation::GetWight()const
{
    return m_weight;
}

size_t COperation::GetTime()const
{
    return m_time;
}

string COperation::GetType()const
{
    return m_type;
}

std::list<size_t> const& COperation::GetNexts()const
{
    return m_nexts;
}

std::list<size_t> const& COperation::GetPrevs()const
{
    return m_prevs;
}

bool COperation::IsUndependent()const
{
    return m_prevs.empty();
}

bool COperation::IsLast()const
{
    return m_nexts.empty();
}

void COperation::AddPrev(size_t id)
{
    m_prevs.push_back(id);
}

void COperation::AddNext(size_t id)
{
    m_nexts.push_back(id);
}

/* Private methods */