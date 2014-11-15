#include "stdafx.h"
#include "TreeIO.h"
#include "Consts.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc <= PARAMS_COUNT)
    {
        cout << "Usage: [Input file name]" << endl;
        return 1;
    }

    CTreeIO treeIO(argv[1]);
    if (treeIO.IsError())
    {
        treeIO.PrintError(cout);
        return 1;
    }

    treeIO.ReadTree();

    return 0;
}