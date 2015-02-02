#include "stdafx.h"
#include "DataBase.h"

void MyAssert(bool i, const char * str);

using namespace std;

DataBase::DataBase()
    : m_index(4)
{
    m_treeBoostPath = boost::filesystem::unique_path();
    ofstream(m_treeBoostPath.string());
}

DataBase::~DataBase()
{
    boost::filesystem::remove(m_treeBoostPath);
}

/* Public methods */

void DataBase::Show(ostream & out)
{
    try
    {
        m_index.Show(out, 1);
    }
    catch (CBTree::Error const& e)
    {
        if (e == CBTree::Error::EmptyTree)
        {
            throw exception("Empty Tree");
        }
        throw;
    }
}

void DataBase::Insert(Uint key, string const& data)
{
    Data dat = { key, true, 0, data };
    dat.pos = Write(dat);
    try
    {
        m_index.Insert(key, dat.pos);
    }
    catch (CBTree::Error const&)
    {
        throw runtime_error("Index file error");
    }
}

void DataBase::Delete(Uint key)
{
    try
    {
        Uint pos = m_index.Search(key);
        Data data = Read(pos);
        data.exists = false;
        Write(data, false);
    }
    catch (CBTree const&)
    {
        throw exception("Data not exists!");
    }
}

string DataBase::GetData(Uint key)
{
    try
    {
        Uint pos = m_index.Search(key);
        Data data = Read(pos);

        if (data.exists)
        {
            return data.data;
        }
        throw CBTree::Error::KeyNotExists;
    }
    catch (CBTree::Error const&)
    {
        throw exception("Data not exists!");
    }
}

/* Private methods */

DataBase::Data DataBase::Read(Uint pos)
{
    ifstream input(m_treeBoostPath.string(), ios::binary);
    MyAssert(!!input, "Data file crashed!");

    Data data;
    Uint size;
    char * tmpStr = new char[MAX_DATA_LENGTH];
    input.seekg(pos);
    input.read(reinterpret_cast<char*>(&(data.key)), sizeof(data.key));
    input.read(reinterpret_cast<char*>(&(data.pos)), sizeof(data.pos));
    input.read(reinterpret_cast<char*>(&(data.exists)), sizeof(data.exists));
    input.read(reinterpret_cast<char*>(&(size)), sizeof(size));
    input.read(tmpStr, size + 1);
    data.data = move(string(tmpStr));
    delete[] tmpStr;
    input.close();
    return data;
}

Uint DataBase::Write(Data const& data, bool isNew)
{
    MyAssert(data.data.size() < MAX_DATA_LENGTH, "Data string so long");

    fstream output(m_treeBoostPath.string(), ios::binary | ios::in | ios::out);
    MyAssert(output.is_open(), "Data file crashed!");

    if (isNew)
        output.seekp(0, ios::end);
    else
        output.seekp(data.pos, ios::beg);

    Uint const currPos = output.tellp();
    Uint listSize = data.data.size();
    output.write(reinterpret_cast<const char*>(&(data.key)), sizeof(data.key));
    output.write(reinterpret_cast<const char*>(&(currPos)), sizeof(currPos));
    output.write(reinterpret_cast<const char*>(&(data.exists)), sizeof(data.exists));
    output.write(reinterpret_cast<const char*>(&(listSize)), sizeof(listSize));
    output.write(data.data.c_str(), data.data.size());

    Uint zero = 0;
    while (listSize++ < MAX_DATA_LENGTH)
    {
        output.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    }
    output.close();
    return currPos;
}

void MyAssert(bool i, const char * str)
{
    if (!i)
    {
        throw runtime_error(str);
    }
}