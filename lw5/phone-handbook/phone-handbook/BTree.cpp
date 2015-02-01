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

            InsertVal(page, it, { 0, key, id });
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

            InsertVal(page, it, { 0, key, id });
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
    MyAssert(m_root != 0, Error::EmptyTree);

    Page page = ReadPage(m_root);
    auto it = page.values.begin();
    while (1)
    {
        Uint link = *it++;
        Uint cKey = *it++;
        Uint cVal = *it++;

        if (cKey == key) return cVal;

        if (key < cKey)
        {
            MyAssert(link != 0, Error::KeyNotExists);
            page = ReadPage(link);
            it = page.values.begin();
            continue;
        }

        if ((++it)-- == page.values.end())
        {
            MyAssert(*it != 0, Error::KeyNotExists);
            page = ReadPage(*it);
            it = page.values.begin();
            continue;
        }
    }
}

/* Private methods */

void CBTree::InsertVal(Page & page, std::list<Uint>::iterator const& it, Element const& elt)
{
    page.values.insert(it, elt.link);
    page.values.insert(it, elt.key);
    page.values.insert(it, elt.val);

    if (page.values.size() > m_chunkCount)
    {
        SplitPage(page);
    }
    else
    {
        WritePage(page, false);
    }
}

void CBTree::SplitPage(Page & sourse)
{
    Page newPage;
    Element middle = SplitVal(sourse, newPage);

    if (sourse.home == 0)
    {
        newPage.pos = WritePage(newPage);
        Page home = { 0, 0, { sourse.pos, middle.key, middle.val, newPage.pos } };
        home.pos = WritePage(home);
        m_root = home.pos;
        WritePage(home, false);
        newPage.home = home.pos;
        WritePage(newPage, false);
        sourse.home = home.pos;
        WritePage(sourse, false);
        return;
    }

    newPage.home = sourse.home;
    newPage.pos = WritePage(newPage);

    Page home = ReadPage(sourse.home);
    auto it = home.values.begin();
    while (1)
    {
        Uint link = *it++;
        Uint cKey = *it++;
        Uint cVal = *it++;
        if (link == sourse.pos)
        {
            --(--it);
            break;
        }
        if ((++it)-- == home.values.end())
        {
            MyAssert(*it == sourse.pos, Error::LinksCollision);
            break;
        }
    }
    home.values.insert(++it, middle.key);
    home.values.insert(it, middle.val);
    home.values.insert(it, newPage.pos);

    if (home.values.size() > m_chunkCount)
    {
        SplitPage(home);
    }
    else
    {
        WritePage(home, false);
    }
}

CBTree::Element CBTree::SplitVal(Page & sourse, Page & newPage)
{
    Uint valCount = (sourse.values.size() - 1) / 3;
    Uint startElt = (valCount % 2 == 0) ? valCount / 2 : (valCount + 1) / 2;
    auto it = sourse.values.begin();
    list<Uint>::iterator eraseStart;

    for (Uint i = 0; i < startElt * 3; ++i) ++it;
    eraseStart = it;
    for (; it != sourse.values.end(); ++it) newPage.values.push_back(*it);

    sourse.values.erase(eraseStart, sourse.values.end());

    Uint val = sourse.values.back();
    sourse.values.pop_back();
    Uint key = sourse.values.back();
    sourse.values.pop_back();
    return { 0, key, val };
}

Uint CBTree::WritePage(Page const& page, bool isNew)
{
    fstream output(m_treeBoostPath.string(), ios::binary | ios::in | ios::out);
    MyAssert(output.is_open(), Error::BtreeFileNotExists);

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
    MyAssert(!!input, Error::BtreeFileNotExists);

    input.seekg(pos, ios::beg);

    MyAssert(!!input, Error::ChunkNotExists);

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


void MyAssert(bool is, CBTree::Error const& err)
{
    if (!is)
    {
        throw err;
    }
}