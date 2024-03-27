#pragma once

#include "Helper.hpp"
#include "Test.hpp"

#include <fstream>

template <class THeap>
class AlternatingTest : private Test<THeap>
{
public:
    using SelfT = AlternatingTest<THeap>;
    using ParentT = Test<THeap>;
    using ParentT::HeapT;

public:
    using ParentT::Test;

    void run()
    {
        Helper::TestResult result;
        for (int i = 1; i <= TEST_PER_RUN_CNT; ++i)
        {
            result += test();
        }
        result /= TEST_PER_RUN_CNT;
        std::ofstream file;
        file.open(m_path, std::ios_base::app);
        file << result << '\n';
    }

private:
    Helper::TestResult test()
    {
        Helper::TestResult result;
        THeap heap;
        for (int counter = 1; counter <= m_size; ++counter)
        {
            for (int i = 1; i <= OPERATION_CNT; ++i)
            {
                auto key = THeap::KeyT::generate();

                auto func = [&]() -> void
                {
                    heap.push(key);
                };

                result += Helper::measure(func);
            }
            for (int i = 1; i <= OPERATION_CNT; ++i)
            {
                auto func = [&]() -> void
                {
                    heap.pop();
                };

                result += Helper::measure(func);
            }
        }
        return result;
    }

private:
    using ParentT::m_path;
    using ParentT::m_size;
    using ParentT::TEST_PER_RUN_CNT;
    static int constexpr OPERATION_CNT = 10;
};
