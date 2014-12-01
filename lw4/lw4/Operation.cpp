#include "stdafx.h"
#include "Operation.h"


COperation::COperation(size_t size)
    :m_size( size )
    ,m_weight( 0 )
{
}


COperation::~COperation()
{
}

/* Public methods */

void COperation::SetWight(size_t weight)
{
    m_weight = weight;
}

size_t COperation::GetWight()const
{
    return m_weight;
}

size_t COperation::GetSize()const
{
    return m_size;
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