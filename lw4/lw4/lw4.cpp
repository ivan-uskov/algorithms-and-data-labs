#include "stdafx.h"
#include "WorkAnalizer.h"
#include <boost\algorithm\string.hpp>

using namespace std;

void PrintOperations(ostream & output, vector<COperation> const& operations)
{
    for (COperation const& oper : operations)
    {
        output << "| " << oper.GetId() << " | " << oper.GetStart() << " | " << oper.GetEnd() << " |" << endl;
        output << "-----------------------------------------------------" << endl;
    }
}

void PrintWorkProcess(ostream & output, CWorkAnalizer::WorkProcess const& process)
{
    for (auto it = process.begin(); it != process.end(); ++it)
    {
        output << "========== " + it->first + " ========================" << endl;
        output << "| id | start | end |" << endl;
        output << "-----------------------------------------------------" << endl;
        PrintOperations(output, it->second);
        output << endl;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        CWorkAnalizer analizer(std::cin);
        CWorkAnalizer::WorkProcess process = analizer.GetProcess();
        PrintWorkProcess(cout, process);
    }
    catch (exception const& e)
    {
        cout << string("Error occured : ") + e.what() << endl;
        return 1;
    }

    return 0;
}