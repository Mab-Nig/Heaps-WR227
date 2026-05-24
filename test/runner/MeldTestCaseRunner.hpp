#pragma once

#include "TestCaseRunner.hpp"
#include "vec_utils.hpp"

template <class THeap>
class MeldTestCaseRunner : public TestCaseRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = MeldTestCaseRunner<THeap>;

public:
    using TestCaseRunner::TestCaseRunner;

    Helper::TestResult operator()() override
    {
        Helper::TestResult result;
        int set_size;
        m_file_in >> set_size;
        THeap heap;
        for (int i = 1; i <= set_size; ++i)
        {
            std::vector<KeyT> array;
            m_file_in >> array;
            THeap tmp(std::make_move_iterator(array.begin()),
                      std::make_move_iterator(array.end()));

            auto func = [&]() -> void
            {
                heap.meld(std::move(tmp));
            };

            result += Helper::measure(func);
        }

        m_file_out << heap.get_size() << '\n';
        while (!heap.is_empty())
        {
            m_file_out << heap.get_top() << ' ';
            heap.pop();
        }
        m_file_out << '\n';

        return result;
    }

private:
    using TestCaseRunner::m_file_in;
    using TestCaseRunner::m_file_out;
};
