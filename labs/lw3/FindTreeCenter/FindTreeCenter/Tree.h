#pragma once
#include "stdafx.h"

class CTree
{

public:

    typedef struct Link
    {
        size_t a, b;
    };

    CTree();
    ~CTree();

    void SetNodeCount(size_t count);
    void AddLink(size_t a, size_t b);
    bool FindRoots(std::vector<size_t> & roots);

private:

    typedef struct Node
    {
        size_t id;
        bool IsLeaf;
        std::list<Link>::const_iterator link;
    };

    size_t m_NodeCount;
    std::list<Link> m_Tree;

    std::list<Link> DeleteLeafs(std::list<Link> const& tree);
    bool AddRoots(std::list<Link> const& links, std::vector<size_t> & roots);
    void AddLeaf(std::list<Node> & leafs, size_t id, std::list<Link>::const_iterator link);
};