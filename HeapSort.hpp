#pragma once

#include <type_traits>
#include <vector>

class HeapSort
{
public:
    HeapSort(int size);

    void shuffle();
    void print();

    template <class THeap, class = std::enable_if_t<
                               std::is_integral_v<typename THeap::KeyT>>>
    void sort()
    {
        THeap heap(m_array.begin(), m_array.end());
        for (int i = m_size - 1; i >= 0; --i)
        {
            m_array[i] = heap.get_top();
            heap.pop();
        }
    }

private:
    int m_size;
    std::vector<int> m_array;
};
