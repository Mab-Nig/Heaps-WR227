#pragma once

#include "HeapSort.hpp"
#include "Helper.hpp"
#include "Test.hpp"

template <class THeap>
class HeapSortTest : public Test<THeap>
{
public:
    using SelfT = HeapSortTest<THeap>;
    using ParentT = Test<THeap>;
    using ParentT::HeapT;

public:
    using ParentT::Test;

private:
    Helper::TestResult test() override
    {
        HeapSort<THeap> heap_sort(m_size);
        heap_sort.shuffle();

        auto func = [&]() -> void
        {
            heap_sort.sort();
        };

        return Helper::measure(func);
    }

private:
    using ParentT::m_path;
    using ParentT::m_size;
    using ParentT::TEST_PER_RUN_CNT;
};
