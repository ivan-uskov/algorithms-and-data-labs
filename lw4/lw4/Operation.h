#pragma once
class COperation
{
public:

    COperation(size_t size);
    ~COperation();

    void AddPrev(size_t id);
    void AddNext(size_t id);
    bool IsUndependent()const;
    std::list<size_t> const& GetNexts()const;

private:
    
    size_t size;
    std::list<size_t> m_prevs, m_nexts;
};

