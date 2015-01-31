#include "stdafx.h"
#include "DataBase.h"

using namespace std;

bool ReadHandBook(istream & input, DataBase<string> & database)
{
    string str, data;
    size_t number;
    while (input.peek() != EOF)
    {
        getline(input, str);
        if (istringstream(str) >> number >> data)
        {
            database.Insert(number, data);
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    try
    {
        CBTree tree(4);
        tree.Insert(14, 88);
        tree.Insert(15, 98);
        tree.Insert(13, 98);
        tree.Insert(12, 98);
        tree.Insert(16, 98);
    }
    catch (exception const& e)
    {
        cout << e.what() << endl;
    }

    /*
    if (argc != 2)
    {
        cout << "Enter handbook file name as second parameter!" << endl;
        return 1;
    }

    ifstream input("handbook");
    if (!input)
    {
        cout << "File not exists" << endl;
        return 1;
    }


    DataBase<string> db;
    ReadHandBook(input, db);
    try
    {
        db.Insert(424000, "Ololosha");

        db.Delete(420000);
        cout << db.GetData(424000) << endl;
    }
    catch (range_error const& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    */
    return 0;
}