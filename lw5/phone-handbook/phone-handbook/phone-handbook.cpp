#include "stdafx.h"
#include "DataBase.h"

using namespace std;

bool ReadHandBook(istream & input, DataBase & database)
{
    string fio;
    Uint number;
    while (input.peek() != EOF)
    {
        if (input >> number)
        {
            getline(input, fio);
            database.Insert(number, fio);
        }
    }
    return true;
}

istringstream GetLineStreamFromIstream(istream & input)
{
    string line;
    getline(input, line);
    return istringstream(line);
}

void ProcessCommand(DataBase & db, istringstream & cmdStrm)
{
    string cmdName;
    if (cmdStrm >> cmdName)
    {
        if (cmdName == "Search")
        {
            Uint key;
            if (cmdStrm >> key)
            {
                try
                {
                    cout << db.GetData(key) << endl;
                }
                catch (exception const& err)
                {
                    cout << err.what() << endl;
                }
            }
        }
        else if (cmdName == "Insert")
        {
            Uint key; string str;
            if (cmdStrm >> key)
            {
                getline(cmdStrm, str);
                db.Insert(key, str);
            }
        }
        else if (cmdName == "Delete")
        {
            Uint key;
            if (cmdStrm >> key)
            {
                try
                {
                    db.Delete(key);
                }
                catch (exception const& err)
                {
                    cout << err.what() << endl;
                }
            }
        }
        else if (cmdName == "Show")
        {
            try
            {
                db.Show(cout);
            }
            catch (exception const& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (cmdName == "exit")
        {
            throw runtime_error("Good Bye!");
        }
    }
}

void Loop(DataBase & db)
{
    while (1)
    {
        cout << "> ";
        string str;
        getline(cin, str);
        ProcessCommand(db, istringstream(str));
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Enter handbook file name as second parameter!" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cout << "File not exists" << endl;
        return 1;
    }

    try
    {
        DataBase db;
        ReadHandBook(input, db);
        Loop(db);
    }
    catch (runtime_error const& err)
    {
        cout << err.what() << endl;
    }
    catch (...)
    {
        cout << "Uncatcheble error occured!" << endl;
    }
    return 0;
}