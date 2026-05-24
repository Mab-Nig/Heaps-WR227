#pragma once

#include "Helper.hpp"
#include "TestCaseRunner.hpp"

template <class THeap>
class AlternatingTestCaseRunner : public TestCaseRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = AlternatingTestCaseRunner<THeap>;

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

            auto func = [&]() -> void
            {
                for (auto&& key : array)
                {
                    heap.push(std::move(key));
                }
                while (!heap.is_empty())
                {
                    heap.pop();
                }
            };
            result += Helper::measure(func);
        }

        return result;
    }

private:
    using TestCaseRunner::m_file_in;
    using TestCaseRunner::m_file_out;
};
