#pragma once
#include "stdafx.h"
#include "Operation.h"

class CReversSortedList
{
public:

    CReversSortedList();
    ~CReversSortedList();

    void Insert(size_t id);
    size_t Pop();
    size_t Size()const;

private:

    std::list<size_t> m_value;

};

