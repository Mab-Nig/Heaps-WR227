#pragma once

#include "Heap.hpp"
#include "Helper.hpp"
#include "TestCaseRunner.hpp"
#include "vec_utils.hpp"

#include <type_traits>

template <class THeap, class = std::enable_if_t<std::is_base_of_v<
                           Heap<typename THeap::KeyT>, THeap>>>
class HeapSortTestCaseRunner : public TestCaseRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = HeapSortTestCaseRunner<THeap>;

public:
    using TestCaseRunner::TestCaseRunner;

    Helper::TestResult operator()() override
    {
        std::vector<KeyT> array;
        m_file_in >> array;

        auto func = [&]() -> void
        {
            THeap heap(std::make_move_iterator(array.begin()),
                       std::make_move_iterator(array.end()));
            for (int i = array.size() - 1; i >= 0; --i)
            {
                array[i] = heap.get_top();
                heap.pop();
            }
        };
        Helper::TestResult result = Helper::measure(func);

        m_file_out << array << '\n';

        return result;
    }

private:
    using TestCaseRunner::m_file_in;
    using TestCaseRunner::m_file_out;
};
