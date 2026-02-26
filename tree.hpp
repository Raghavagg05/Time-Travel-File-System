#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include "str_hashmap.hpp"
#include "int_hashmap.hpp"
using namespace std;

class TreeNode
{
private:
    int version_id;
    string content;
    string message;
    time_t create_ts;
    time_t snap_ts;
    TreeNode *parent;
    vector<TreeNode *> children;

public:
    TreeNode(string contnt = "", int version = 0, string text = "Changes to file done")
    {
        create_ts = time(0);
        content = contnt;
        version_id = version;
        message = text;
        snap_ts = 0;
        parent = NULL;
    }

    void add_child(TreeNode *child)
    {
        children.push_back(child);
    }

    void set_par(TreeNode *par) { parent = par; }

    TreeNode *get_par() { return parent; }

    string get_content() { return content; }

    int get_version() { return version_id; }

    void set_content(string contnt = "") { content = contnt; }

    time_t get_timestamp() { return create_ts; }

    void set_message(string msg = "") { message = msg; }

    string get_message() { return message; }

    void set_snapshot() { snap_ts = time(0); }

    bool is_snapshot()
    {
        if (snap_ts != 0)
            return true;
        else
            return false;
    }
};

class Tree
{
private:
    TreeNode *root;
    TreeNode *active_version;
    HashMapInt<int, TreeNode *> version_map;
    int total_versions;

public:
    Tree() : version_map(1000)
    {
        root = NULL;
        active_version = NULL;
        total_versions = 0;
    }

    int get_active_version()
    {
        return active_version->get_version();
    }

    void create()
    {
        root = new TreeNode("", 0, "snapshot created");
        active_version = root;
        active_version->set_snapshot();
        version_map.put(0, root);
    }

    string read()
    {
        if (active_version != NULL)
            return active_version->get_content();
        else
            return "file does't exist!";
    }

    void snapshot(string msg = "Snapshot taken")
    {
        if (active_version != NULL)
        {   
            if(active_version->is_snapshot()){
                cout<<"Already marked as snapshot!\n";
            }
            active_version->set_message(msg);
            active_version->set_snapshot();
        }
    }
    // true if new version created
    bool insert(string contnt)
    {
        if (active_version == NULL)
            return false;
        string old_contnt = active_version->get_content();
        if (active_version->is_snapshot())
        {
            total_versions++;
            TreeNode *next = new TreeNode(old_contnt + contnt, total_versions);
            active_version->add_child(next);
            next->set_par(active_version);
            active_version = next;
            version_map.put(next->get_version(), next);
            return true;
        }
        else
        {
            active_version->set_content(old_contnt + contnt);
            return false;
        }
    }
    // true if new version created
    bool update(string contnt)
    {
        if (active_version == NULL)
            return false;

        if (active_version->is_snapshot())
        {
            total_versions++;
            TreeNode *next = new TreeNode(contnt, total_versions);
            active_version->add_child(next);
            next->set_par(active_version);
            active_version = next;
            version_map.put(next->get_version(), next);
            return true;
        }
        else
        {
            active_version->set_content(contnt);
            return false;
        }
    }

    void rollback(int given_id = -1)
    {
        if (active_version == NULL)
            return;

        if (given_id != -1)
        {
            if (version_map.contains(given_id))
                active_version = version_map.get(given_id);
            else{
                cout<<"Given version does'nt exist!\n";
            }
        }
        else
            if(!active_version->get_par()){
                cout<<"Parent version does not exist!\n";
                return;
            }
            active_version = active_version->get_par();
    }

    void history()
    {
        TreeNode *cur = active_version;
        while (cur != NULL)
        {
            if (cur->is_snapshot())
            {
                cout << "version_id: " << cur->get_version() << " timestamp: " << cur->get_timestamp() << " message: " << cur->get_message() << "\n";
            }
            cur = cur->get_par();
        }
    }
};
#endif // TREE_HPP
