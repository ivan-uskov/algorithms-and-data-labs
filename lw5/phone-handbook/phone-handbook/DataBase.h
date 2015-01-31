#pragma once
#include <vector>
#include <string>
#include <map>
#include <exception>
#include "BTree.h"

template <class DataType>
class DataBase
{

public:

    DataBase(){}
    ~DataBase(){}

    void Insert(size_t number, DataType const& data)
    {
        m_tree[number] = m_data.size();
        m_data.push_back({ number, true, data });
    }

    void Delete(size_t number)
    {
        m_data[GetDataId(number)].exists = false;
    }

    DataType GetData(size_t number)
    {
        size_t id = GetDataId(number);

        if (!m_data[id].exists)
        {
            throw range_error("This data is now deleted!");
        }

        return m_data[id].data;
    }

private:

    struct Row
    {
        size_t key;
        bool exists;
        DataType data;
    };

    size_t capacity;
    std::vector<Row> m_data;
    std::map<size_t, size_t> m_tree;

    size_t GetDataId(size_t number)
    {
        auto id = m_tree.find(number);
        if (id == m_tree.end())
        {
            throw range_error("This data doesn't exists!");
        }
        return id->second;
    }
};

struct Data
{
    Data(size_t k, size_t id)
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

