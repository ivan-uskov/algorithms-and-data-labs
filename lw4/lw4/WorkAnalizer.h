#pragma once
#include "stdafx.h"
#include "Operation.h"
#include "ReversSortedList.h"

class CWorkAnalizer
{
public:

    CWorkAnalizer(std::istream & input);
    ~CWorkAnalizer();

    bool IsError()const;
    void PrintError()const;

    bool GetWay(std::vector<size_t> & way);

private:
    
    enum class Error
    {
        None,
        ParseOperationSizes,
        ParseLinks,
        InvalidGraph
    };

    Error m_error;
    size_t m_operationsCount;
    std::vector<COperation> m_operations;
    std::list<size_t> m_availeble;    
    
    bool ReadOperations(std::string const& operationsSizes);
    bool ReadLinks(std::istream & input);
    bool ReadLink(std::string const& linkString);

    bool InitStartPoint(size_t & startPoint);
    bool InitEndPoint(size_t & endPoint);
    bool InitPoint(size_t & endPoint, std::function<bool(COperation)> fn);

    size_t GetMaxAvaileble()const;
    void DeleteFromAvaileble(size_t id);

    void InitOperationsWeight(size_t id, size_t weight);

};

