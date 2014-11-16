#include "stdafx.h"
#include "Tree.h"

using namespace std;

CTree::CTree()
{
}


CTree::~CTree()
{
}

/* Public methods */

void CTree::SetNodeCount(size_t count)
{
    m_NodeCount = count;
}

void CTree::AddLink(size_t a, size_t b)
{
    m_Tree.push_back({a, b});
}

bool CTree::FindRoots(vector<size_t> & roots)
{
    list<Link> links = DeleteLeafs(m_Tree);

    return AddRoots(links, roots);
}

/* Private methods */

void CTree::AddLeaf(std::list<Node> & leafs, size_t id, list<Link>::const_iterator link)
{
    for (Node & leaf : leafs)
    {
        if (leaf.id == id)
        {
            leaf.IsLeaf = false;
            return;
        }
    }

    Node * node = new Node;
    node->id = id;
    node->IsLeaf = true;
    node->link = link;
    leafs.push_back(*node);
}

list<CTree::Link> CTree::DeleteLeafs(std::list<Link> const& tree)
{
    list<Link> links = tree;

    while (links.size() > 2)
    {
        list<Node> leafs;
        for (auto it = links.begin(); it != links.end(); ++it)
        {
            AddLeaf(leafs, it->a, it);
            AddLeaf(leafs, it->b, it);
        }
        for (Node & leaf : leafs)
        {
            if (leaf.IsLeaf)
            {
                links.erase(leaf.link);
            }
        }
    }
    return links;
}

bool CTree::AddRoots(std::list<Link> const& links, std::vector<size_t> & roots)
{
    if (links.size() == 2)
    {
        const Link * one = &links.front();
        const Link * two = &links.back();
        if (one->a == two->a || one->a == two->b)
        {
            roots.push_back(one->a);
        }
        else if (one->b == two->a || one->b == two->b)
        {
            roots.push_back(one->b);
        }
    }
    else if (links.size() == 1)
    {
        const Link * link = &links.back();
        roots.push_back(link->a);
        roots.push_back(link->b);
    }
    else
    {
        return false;
    }
    return true;
}