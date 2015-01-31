#include "stdafx.h"
#include "Finder.h"

using namespace std;

bool ReadLinks(CFinder & finder)
{
    while (cin.peek() != EOF)
    {
        size_t x, y;
        string str;
        getline(cin, str);
        if (!(istringstream(str) >> x >> y))
        {
            return false;
        }
        finder.AddLink(x, y);
    }
    return true;
}

void PrintCenter(vector<size_t> center)
{
    ostream_iterator<size_t> output(cout, " ");
    copy(center.begin(), center.end(), output);
}

int main(int argc, char* argv[])
{
    CFinder finder;
    if (ReadLinks(finder))
    {
        PrintCenter(finder.GetCenter());
    }

    return 0;
}

