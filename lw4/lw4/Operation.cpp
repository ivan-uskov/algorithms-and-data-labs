#include "stdafx.h"
#include "Operation.h"


COperation::COperation(size_t size)
    :size( size )
    ,weight( 0 )
{
}


COperation::~COperation()
{
}

/* Public methods */

std::list<size_t> const& COperation::GetNexts()const
{
    return m_nexts;
}

bool COperation::IsUndependent()const
{
    return m_prevs.empty();
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