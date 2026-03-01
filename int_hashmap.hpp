#ifndef INT_HASHMAP_HPP
#define INT_HASHMAP_HPP

#include <vector>
#include <utility>
#include <string>
using namespace std;

template <typename K, typename V>
class HashMapInt
{
private:
    vector<vector<pair<K, V>>> table;
    int capacity;
    int size;

    int hash(K key) const
    {
        return (key % capacity);
    }

public:
    HashMapInt(int cap = 10001)
    {
        capacity = cap;
        table.resize(capacity);
        size = 0;
    }

    void put(const K &key, const V &value)
    {
        int h_val = hash(key);
        for (auto &p : table[h_val])
        {
            if (p.first == key)
            {
                p.second = value;
                return;
            }
        }
        table[h_val].push_back({key, value});
        size++;
    }

    V get(const K &key) const
    {
        int h_val = hash(key);
        for (const auto &p : table[h_val])
        {
            if (p.first == key)
                return p.second;
        }
    }

    bool contains(const K &key) const
    {
        int h_val = hash(key);
        for (const auto &p : table[h_val])
        {
            if (p.first == key)
                return true;
        }
        return false;
    }
};

#endif 
