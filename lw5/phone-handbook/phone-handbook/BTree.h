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

    CBTree(Uint count);
    ~CBTree();

    bool Search(Uint key);
    void Insert(Uint key, Uint id);

private:

    struct Page
    {
        Uint home;
        std::list<Uint> values;
    };

    Uint m_root;
    Uint m_pageCount;
    Uint m_pageSize;
    Uint m_chunkCount;
    
    boost::filesystem::path m_treeBoostPath;

    Uint WritePage(Page const& page);
    Page ReadPage(Uint const& pos);

};