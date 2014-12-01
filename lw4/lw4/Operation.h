#pragma once
class COperation
{
public:

    COperation(size_t size);
    ~COperation();

    void AddPrev(size_t id);
    void AddNext(size_t id);
    void SetWight(size_t weight);
    size_t GetWight()const;
    size_t GetSize()const;
    bool IsUndependent()const;
    bool IsLast()const;
    std::list<size_t> const& GetNexts()const;
    std::list<size_t> const& GetPrevs()const;

private:
    
    size_t m_size;
    size_t m_weight;
    std::list<size_t> m_prevs, m_nexts;
};

