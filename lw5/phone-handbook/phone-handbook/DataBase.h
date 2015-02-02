#pragma once
#include <vector>
#include <string>
#include <map>
#include <exception>
#include "BTree.h"

class DataBase
{

public:

    static const int MAX_DATA_LENGTH = 255;

    DataBase();
    ~DataBase();

    void Insert(Uint key, std::string const& data);
    void Delete(Uint key);
    std::string GetData(Uint key);
    void Show(std::ostream & out);

private:

    struct Data
    {
        Uint key;
        bool exists;
        Uint pos;
        std::string data;
    };

    boost::filesystem::path m_treeBoostPath;
    CBTree m_index;

    Data Read(Uint pos);
    Uint Write(Data const& data, bool isNew = true);

};
