#pragma once
#include <map>
#include <vector>
#include <queue>

class CFinder
{
public:

    CFinder();
    ~CFinder();

    void AddLink(size_t link1Id, size_t link2Id);
    std::vector<size_t> GetCenter();

private:
    
    std::map<size_t, std::vector<size_t>> m_points;

    void InitLeafs(std::queue<size_t> & leafs);
    void DeleteLink(size_t id, size_t linkId);
};

