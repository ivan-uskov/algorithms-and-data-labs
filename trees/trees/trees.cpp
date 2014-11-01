#include "stdafx.h"

using namespace std;

enum class StreamErrors
{
    FileNotExists,
    ComputerNumber,
    LinksFormat,
    None
};

struct TreeInfo
{
    unsigned count;
    
};

bool ReadLink(ifstream &input)
{
    double x, y;
    return (input >> x >> y) ? true : false;
}

bool ReadLinks(ifstream &input, TreeInfo &info)
{
    while (!input.eof())
    {
        
    }
    return true;
}

StreamErrors ReadTree(const char *fileName, TreeInfo &info)
{
    ifstream input(fileName);
    if (input.bad())
    {
        return StreamErrors::FileNotExists;
    }

    if (!(input >> info.count))
    {
        return StreamErrors::ComputerNumber;
    }

    if (ReadLinks(input, info))
    {
        return StreamErrors::None;
    }
    else
    {
        return StreamErrors::LinksFormat;
    }
}

int main(int argc, char* argv[])
{
    const int PARAMS_COUNT = 2;
    if (argc <= PARAMS_COUNT)
    {
        cout << "Usage: [Input file name]";
        return 1;
    }


    return 0;
}