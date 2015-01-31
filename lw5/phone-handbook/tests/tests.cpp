#include "stdafx.h"
#include "../phone-handbook/BTree.h"

struct Data
{
    Data(size_t k,  size_t id)
        : m_key(k)
        , m_id(id)
    {

    }
    ~Data()
    {

    }

    size_t m_key, m_id;

    bool operator <(Data const& data)
    {
        return m_key < data.m_key;
    }

    bool operator ==(Data const& data)
    {
        return m_key == data.m_key;
    }
};

BOOST_AUTO_TEST_CASE(CBTreeTests)
{
    CBTree<Data> tree(2);


}