#include <iostream>
#include <sstream>
#include <string>
#include "filesystem.hpp"
using namespace std;

int main()
{
    FileSystem filesys;
    string line;

    cout << "Enter operation:\n";

    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string operation;
        ss >> operation;

        if (operation == "CREATE")
        {
            string filename;
            ss >> filename;
            if (filename == "")
                cout << "No name of the file given!\n";
            else
                filesys.CREATE(filename);
        }
        else if (operation == "READ")
        {
            string filename;
            ss >> filename;
            if (filename == "")
                cout << "No name of the file given!\n";
            else
                filesys.READ(filename);
        }
        else if (operation == "INSERT")
        {
            string filename, content;
            ss >> filename;
            if (filename == "")
            {
                cout << "No name of the file given!\n";
                continue;
            }
            getline(ss, content);
            if (content == "")
            {
                cout << "No content for the file given!\n";
                continue;
            }
            if (!content.empty() && content[0] == ' ')
                content.erase(0, 1); // remove leading space
            filesys.INSERT(filename, content);
        }
        else if (operation == "UPDATE")
        {
            string filename, content;
            ss >> filename;
            getline(ss, content);
            if (!content.empty() && content[0] == ' ')
                content.erase(0, 1);
            filesys.UPDATE(filename, content);
        }
        else if (operation == "SNAPSHOT")
        {
            string filename, message;
            ss >> filename;
            getline(ss, message);
            if (!message.empty() && message[0] == ' ')
                message.erase(0, 1);
            filesys.SNAPSHOT(filename, message);
        }
        else if (operation == "ROLLBACK")
        {
            string filename;
            int version_id;
            ss >> filename;
            if (ss >> version_id)
            {
                filesys.ROLLBACK(filename, version_id);
            }
            else
            {
                filesys.ROLLBACK(filename);
            }
        }
        else if (operation == "HISTORY")
        {
            string filename;
            ss >> filename;
            filesys.HISTORY(filename);
        }
        else if (operation == "RECENT_FILES")
        {
            int n;
            ss >> n;
            filesys.RECENT_FILES(n);
        }
        else if (operation == "BIGGEST_TREES")
        {
            int n;
            ss >> n;
            filesys.BIGGEST_TREES(n);
        }
        else if (operation == "EXIT")
        {
            cout << "Program ended\n";
            break;
        }
        else
        {
            cout << "No such operation exists!\n";
        }
    }

    return 0;
}
