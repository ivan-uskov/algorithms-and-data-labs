#pragma once
#include "stdafx.h"
#include "Operation.h"

class CWorkAnalizer
{
public:

    typedef std::map<std::string, std::vector<COperation>> WorkProcess;

    CWorkAnalizer(std::istream & input);
    ~CWorkAnalizer();

    WorkProcess GetProcess();

private:

    size_t m_operationsCount;
    std::vector<COperation> m_operations;
    std::list<size_t> m_availeble;

    size_t ReadOperationCount(std::istream & input);
    void ReadOperations(std::istream & input, size_t operationsCount);
    void ReadOperation(std::string const& operationStr);
    void ReadLinks(std::istream & input);
    void ReadLink(std::string const& linkString);

    size_t GetStartPoint();
    size_t GetEndPoint();
    size_t GetPoint(std::function<bool(COperation)> fn);
    size_t GetOperationById(size_t id);
    std::map<std::string, size_t> GetTimeLine()const;

    std::list<size_t> GetMaxAvailebles()const;
    void EraseFromAvaileble(size_t id);
    void EraseFromChilds(size_t id);

    void InitOperationsWeight(size_t id, size_t weight = 0);

};

