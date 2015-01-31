#include "stdafx.h"
#include "Finder.h"

using namespace std;

CFinder::CFinder()
{
}


CFinder::~CFinder()
{
}

void CFinder::AddLink(size_t link1Id, size_t link2Id)
{
    m_points[link1Id].push_back(link2Id);
    m_points[link2Id].push_back(link1Id);
}

vector<size_t> CFinder::GetCenter()
{
    vector<size_t> center;
    queue<size_t> leafs;
    InitLeafs(leafs);

    while (m_points.size() && leafs.size() > 0)
    {
        size_t currLeaf = leafs.front();
        size_t next = m_points[currLeaf][0];

        DeleteLink(next, currLeaf);

        if (m_points[next].size() == 1)
        {
            leafs.push(next);
        }

        m_points.erase(currLeaf);
        leafs.pop();
    }

    while (leafs.size() > 0)
    {
        center.push_back(leafs.front());
        leafs.pop();
    }

    return center;
}

/* Private methods */

void CFinder::InitLeafs(std::queue<size_t> & leafs)
{
    auto CopyLeaf = [&leafs](pair<size_t, vector<size_t>> const& point)
    {
        if (point.second.size() == 1)
        {
            leafs.push(point.first);
        }
    };
    for_each(m_points.begin(), m_points.end(), CopyLeaf);
}

void CFinder::DeleteLink(size_t id, size_t linkId)
{
    auto it = find_if(m_points[id].begin(), m_points[id].end(), [linkId](size_t elt){return elt == linkId; });
    if (it != m_points[id].end())
    {
        m_points[id].erase(it);
    }
}