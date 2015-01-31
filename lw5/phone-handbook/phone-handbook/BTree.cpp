#include "stdafx.h"
#include "BTree.h"

using namespace std;

void MyAssert(bool is, const char * str);

CBTree::CBTree(Uint count)
    : m_pageCount(count)
    , m_root(0)
    , m_chunkCount(count * 3 + 1)
{
    m_treeBoostPath = boost::filesystem::unique_path();
    ofstream(m_treeBoostPath.string()) << "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
}

CBTree::~CBTree()
{
    boost::filesystem::remove(m_treeBoostPath);
}

/* Public methods */

void CBTree::Insert(Uint const key, Uint const id)
{
    if (m_root == 0)
    {
        Page page = { 0, 0, { 0, key, id, 0 } };
        m_root = WritePage(page);
        return;
    }

    Page page = ReadPage(m_root);
    auto it = page.values.begin();

    while (1)
    {
        Uint link = *it++;
        Uint cKey = *it++;
        Uint cVal = *it;

        if (key < cKey)
        {
            --(--it);
            if (*it != 0)
            {
                page = ReadPage(*it);
                it = page.values.begin();
                continue;
            }

            InsertVal(page, it, key, id);
            return;
        }

        ++(++it);
        if (it == page.values.end())
        {
            --it;
            if (*it != 0)
            {
                page = ReadPage(*it);
                it = page.values.begin();
                continue;
            }

            InsertVal(page, it, key, id);
            return;
        }
        else
        {
            --it;
        }
    }
}

Uint CBTree::Search(Uint const key)
{
    MyAssert(m_root == 0, "Empty tree");

    return 1;
}

/* Private methods */

void CBTree::InsertVal(Page & page, std::list<Uint>::iterator const& it, Uint const key, Uint const id)
{
    page.values.insert(it, 0);
    page.values.insert(it, key);
    page.values.insert(it, id);

    if (page.values.size() > m_chunkCount)
    {
        Page page1, page2;
        SplitPage(page, page1, page2);
    }
    else
    {
        WritePage(page, false);
    }
}

void CBTree::SplitPage(Page & sourse, Page & res1, Page & res2)
{
    if (sourse.home == 0)
    {
        res1.home = sourse.home;

    }

    throw exception("page ololp");
}

Uint CBTree::WritePage(Page const& page, bool isNew)
{
    fstream output(m_treeBoostPath.string(), ios::binary | ios::in | ios::out);
    MyAssert(output.is_open(), "Index file lost!");

    if (isNew)
        output.seekp(0, ios::end);
    else
        output.seekp(page.pos, ios::beg);

    Uint currPos = output.tellp();
    Uint listSize = page.values.size();
    output.write(reinterpret_cast<const char*>(&(page.home)), sizeof(page.home));
    output.write(reinterpret_cast<const char*>(&(currPos)), sizeof(currPos));
    output.write(reinterpret_cast<const char*>(&(listSize)), sizeof(listSize));

    for (Uint num : page.values)
    {
        output.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    Uint zero = 0;
    while (listSize++ < m_chunkCount)
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
    input.read(reinterpret_cast<char*>(&page.pos), sizeof(page.pos));
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