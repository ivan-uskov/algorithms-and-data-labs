#include "stdafx.h"
#include "ReversSortedList.h"

CReversSortedList::CReversSortedList()
{
}

CReversSortedList::~CReversSortedList()
{
}

/* Public methods */

void CReversSortedList::Insert(size_t id)
{
    auto it = m_value.begin();
    for (; it != m_value.end(); ++it)
    {
        if (*it < id)
        {
            m_value.emplace(it, id);
        }
    }

    if (it == m_value.end())
    {
        m_value.push_back(id);
    }
}

size_t CReversSortedList::Pop()
{
    size_t id = m_value.front();
    m_value.pop_front();
    return id;
}

size_t CReversSortedList::Size()const
{
    return m_value.size();
}
