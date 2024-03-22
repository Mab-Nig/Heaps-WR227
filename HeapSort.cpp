#include "HeapSort.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

HeapSort::HeapSort(int size)
    : m_size(size),
      m_array(size)
{
    std::iota(m_array.begin(), m_array.end(), 0);
}

void HeapSort::shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(m_array.begin(), m_array.end(), gen);
}

void HeapSort::print()
{
    for (int x : m_array)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
