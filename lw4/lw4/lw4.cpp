#include "stdafx.h"
#include "WorkAnalizer.h"

int main(int argc, char* argv[])
{
    CWorkAnalizer analizer(std::cin);
    if (analizer.IsError())
    {
        analizer.PrintError();
        return 1;
    }

    std::vector<size_t> way;
    analizer.GetWay(way);

	return 0;
}