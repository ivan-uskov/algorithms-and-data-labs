#include "stdafx.h"
#include "BTree.h"


using namespace std;

void MyAssert(bool is, const char * str);

CBTree::CBTree(Uint count)
    : m_pageCount(count)
    , m_root(0)
    , m_chunkCount(count * 3 + 3)
    , m_pageSize(m_chunkCount  * sizeof(Uint))
{
    m_treeBoostPath = boost::filesystem::unique_path();
    ofstream(m_treeBoostPath.string()) << "Start\n";
}

CBTree::~CBTree()
{
    //boost::filesystem::remove(m_treeBoostPath);
}

/* Public methods */

void CBTree::Insert(Uint key, Uint id)
{
    Page page({ 4, {0,2,3,0} });
    Uint a = WritePage(page);

    Page p = ReadPage(a);
    MyAssert(p.home == 4 && p.values == list<Uint>({ 0, 2, 3, 0 }), "Ololo");
}

bool CBTree::Search(Uint key)
{
    cout << "pageSize : " << m_pageSize << endl;
    return true;
}

/* Private methods */

Uint CBTree::WritePage(Page const& page)
{
    ofstream output(m_treeBoostPath.string(), ios::app | ios::binary);
    MyAssert(!!output, "Index file lost!");

    output.seekp(0, ios::end);
    Uint currPos = output.tellp();
    Uint listSize = page.values.size();
    output.write(reinterpret_cast<const char*>(&(page.home)), sizeof(page.home));
    output.write(reinterpret_cast<const char*>(&(listSize)), sizeof(listSize));

    for (Uint num : page.values)
    {
        output.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    Uint zero = 0;
    while (listSize++ <= m_chunkCount)
    {
        output.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    }
    output.close();
    return currPos;
}

CBTree::Page CBTree::ReadPage(Uint const& pos)
{
    ifstream input(m_treeBoostPath.string(), ios::binary);
    MyAssert(!!input, "BTree file not exists!");

    input.seekg(pos, ios::beg);

    MyAssert(!!input, "Chunck not exists");

    Page page;
    Uint count, i;
    input.read(reinterpret_cast<char*>(&page.home), sizeof(page.home));
    input.read(reinterpret_cast<char*>(&count), sizeof(count));

    while (count-- > 0)
    {
        input.read(reinterpret_cast<char*>(&i), sizeof(i));
        page.values.push_back(i);
    }

    input.close();
    return page;
}


void MyAssert(bool is, const char * str)
{
    if (!is)
    {
        throw exception(str);
    }
}