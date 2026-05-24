#pragma once

#include "Helper.hpp"
#include "TestCaseRunner.hpp"

template <class THeap>
class SequentialTestCaseRunner : public TestCaseRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = SequentialTestCaseRunner<THeap>;

public:
    using TestCaseRunner::TestCaseRunner;

    Helper::TestResult operator()() override
    {
        Helper::TestResult result;
        THeap heap;
        std::vector<KeyT> array;
        m_file_in >> array;

        auto func_1 = [&]() -> void
        {
            for (auto&& key : array)
            {
                heap.push(std::move(key));
            }
        };
        result = Helper::measure(func_1);

        auto func_2 = [&]() -> void
        {
            while (!heap.is_empty())
            {
                heap.pop();
            }
        };
        m_deletion_only_result = Helper::measure(func_2);

        return result;
    }

    Helper::TestResult get_deletion_only_result() const
    {
        return m_deletion_only_result;
    }

private:
    using TestCaseRunner::m_file_in;
    using TestCaseRunner::m_file_out;

    Helper::TestResult m_deletion_only_result;
};
