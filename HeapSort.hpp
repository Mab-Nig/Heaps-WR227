#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

template <class THeap>
class HeapSort
{
public:
    HeapSort(int size)
        : m_size(size),
          m_array(size)
    {
    }

    void shuffle()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(m_array.begin(), m_array.end(), gen);
    }

    void print()
    {
        for (int x : m_array)
        {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }

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
    std::vector<typename THeap::KeyT> m_array;
};
