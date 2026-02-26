#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include "str_hashmap.hpp"
using namespace std;

template <typename var_type>
class Heap
{
private:
    vector<var_type> heap;
    HashMapStr<string, int> pos; // maps filename -> index

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void swap_nodes(int i, int j)
    {
        swap(heap[i], heap[j]);
        pos.put(heap[i].first, i);
        pos.put(heap[j].first, j);
    }

    void up_traverse(int i)
    {
        while (i > 0 && heap[i].second > heap[parent(i)].second)
        {
            swap_nodes(i, parent(i));
            i = parent(i);
        }
    }

    void down_traverse(int i)
    {
        int n = heap.size();
        while (true)
        {
            int l = left(i), r = right(i), next = i;

            if (l < n && heap[l].second > heap[next].second)
                next = l;
            if (r < n && heap[r].second > heap[next].second)
                next = r;

            if (next == i)
                break;
            swap_nodes(i, next);
            i = next;
        }
    }

public:
    void push(const var_type &value)
    {
        heap.push_back(value);
        int idx = heap.size() - 1;
        pos.put(value.first, idx);
        up_traverse(idx);
    }

    var_type pop()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        var_type popped = heap[0];
        pos.put(popped.first, -1); // mark as removed

        if (heap.size() == 1)
        {
            heap.pop_back();
            return popped;
        }
        heap[0] = heap.back();
        pos.put(heap[0].first, 0);
        heap.pop_back();
        down_traverse(0);
        return popped;
    }

    var_type top()
    {
        return heap[0];
    }

    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }

    void update(const string &filename, const typename var_type::second_type &new_val)
    {
        int idx = pos.get(filename);
        auto old_val = heap[idx].second;
        heap[idx].second = new_val;

        if (new_val > old_val)
        {
            up_traverse(idx);
        }
        else if (new_val < old_val)
        {
            down_traverse(idx);
        }
    }
};
#endif // HEAP_HPP
