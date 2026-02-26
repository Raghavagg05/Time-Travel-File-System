#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <iostream>
#include <string>
#include <ctime>
#include "tree.hpp"
#include "heap.hpp"
#include "str_hashmap.hpp"
using namespace std;

class FileSystem
{
private:
    HashMapStr<string, Tree *> files;
    Heap<pair<string, time_t>> mtime_heap;
    Heap<pair<string, int>> vcount_heap;

public:
    void CREATE(string filename)
    {
        if (files.contains(filename))
            cout << "File already exists!\n";
        else
        {
            Tree *cur = new Tree();
            cur->create();
            files.put(filename, cur);
            vcount_heap.push({filename,1});
            mtime_heap.push({filename,time(0)});
            cout << "File with name " << filename << " created!\n";
        }
    }

    void READ(string filename)
    {
        if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
            cout << files.get(filename)->read() << "\n";
    }

    void INSERT(string filename, string contnt)
    {
        if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
        {
            // true if new version created
            bool check = files.get(filename)->insert(contnt);
            if (check)
            {
                vcount_heap.update(filename,files.get(filename)->get_active_version());
                cout << "new version for " << filename << " with version " << files.get(filename)->get_active_version() << " created\n";
            }
            else
                cout << contnt << " added to " << filename << "'s current version: (" << files.get(filename)->get_active_version() << ")\n";
            mtime_heap.update(filename,time(0));
        }
    }

    void UPDATE(string filename, string content)
    {
        if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
        {
            // true if new version created
            bool check = files.get(filename)->update(content);
            if (check)
            {
                vcount_heap.update(filename, files.get(filename)->get_active_version());
                cout << "new version " << files.get(filename)->get_active_version() << " created\n";
            }
            else
                cout << filename << "'s current version's content updated(version: " << files.get(filename)->get_active_version() << ")\n";
            mtime_heap.update(filename, time(0));
        }
    }

    void SNAPSHOT(string filename, string message = "deafult snapshot message")
    {
        if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
        {
            files.get(filename)->snapshot(message);
            mtime_heap.update(filename, time(0));
            cout << "Snapshot created for " << filename << "(active version: " << files.get(filename)->get_active_version() << ")\n";
        }
    }

    void ROLLBACK(string filename, int version_id = -1)
    {
        if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
        {
            files.get(filename)->rollback(version_id);
            cout << "Active version id set to " << files.get(filename)->get_active_version() << "\n";
            mtime_heap.update(filename, time(0));
        }
    }

    void HISTORY(string filename)
    {   
        if(filename=="")cout<<"Filename not given!\n";
        else if (!files.contains(filename))
            cout << "File does not exist!\n";
        else
            files.get(filename)->history();
    }

    void RECENT_FILES(int num)
    {

        if (num > mtime_heap.size())
        {
            cout << num << " exceeds the number of files present currently!\n";
            return;
        }
        cout << "Most recent files:\n";
        vector<pair<string,time_t>> v;
        for (int i = 0; i < num; i++)
        {
            pair<string, time_t> temp = mtime_heap.pop();
            v.push_back(temp);
            cout << temp.first << " (last modified: " << temp.second << ")\n";
        }
        for(int i=0;i<v.size();i++)mtime_heap.push(v[i]);
    }

    void BIGGEST_TREES(int num)
    {

        if (num > vcount_heap.size())
        {
            cout << num << " exceeds the number of files present currently!\n";
            return;
        }

        cout << "Biggest trees:\n";
        vector<pair<string,int>> v;
        for (int i = 0; i < num; i++)
        {
            pair<string, int> temp = vcount_heap.pop();
            v.push_back(temp);
            cout << temp.first << " (version count: " << temp.second + 1 << ")\n";
        }
        for(int i=0;i<v.size();i++)vcount_heap.push(v[i]);
    }
};

#endif