#pragma once
class COperation
{
public:

    COperation(size_t id, size_t time, std::string type);
    ~COperation();

    void AddPrev(size_t id);
    void AddNext(size_t id);

    void SetWight(size_t weight);
    void SetExecutionTime(size_t start);

    size_t GetId()const;
    size_t GetWight()const;
    size_t GetTime()const;
    size_t GetStart()const;
    size_t GetEnd()const;
    std::string GetType()const;
    std::list<size_t> const& GetNexts()const;
    std::list<size_t> const& GetPrevs()const;

    void ErasePrev(size_t id);
    bool IsUndependent()const;
    bool IsLast()const;

private:
    size_t m_id;
    size_t m_time;
    size_t m_weight;
    size_t m_start, m_end;
    std::string m_type;
    std::list<size_t> m_prevs, m_nexts;
};

