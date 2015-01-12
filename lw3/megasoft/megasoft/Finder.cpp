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
    queue<size_t> leafs;
}

/* Private methods */

void CFinder::InitLeafs(std::queue<size_t> leafs)
{
    auto CopyLeaf = [&leafs](pair<size_t, vector<size_t>> point)
    {
        if (point.second.size() == 1)
        {
            leafs.push(point.first);
        }
    };
    for_each(m_points.begin(), m_points.end(), CopyLeaf);
}