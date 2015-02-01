#pragma once
#include <boost/filesystem.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include <memory>
#include <list>

typedef boost::uint64_t Uint;

class CBTree
{

public:

    enum class Error
    {
        KeyNotExists,
        EmptyTree,
        ChunkNotExists,
        BtreeFileNotExists,
        LinksCollision
    };

    CBTree(Uint count);
    ~CBTree();

    Uint Search(Uint const key);
    void Insert(Uint const key, Uint const id);

private:

    struct Page
    {
        Uint home;
        Uint pos;
        std::list<Uint> values;
    };

    struct Element
    {
        Uint link;
        Uint key;
        Uint val;
    };

    Uint m_root;
    Uint m_pageCount;
    Uint m_chunkCount;

    boost::filesystem::path m_treeBoostPath;

    Uint WritePage(Page const& page, bool isNew = true);
    Page ReadPage(Uint const& pos);
    void InsertVal(Page & page, std::list<Uint>::iterator const& it, Element const& elt);
    void SplitPage(Page & sourse);
    Element SplitVal(Page & sourse, Page & newPage);
};