#pragma once

#include "Helper.hpp"
#include "Test.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

template <class THeap>
class SequentialTest : public Test<THeap>
{
public:
    using SelfT = SequentialTest<THeap>;
    using ParentT = Test<THeap>;
    using ParentT::HeapT;

public:
    SequentialTest(int size, std::filesystem::path insertion_path,
                   std::filesystem::path deletion_path)
        : m_insertion_path(insertion_path),
          m_deletion_path(deletion_path)
    {
        m_size = size;
    }

    void run() override
    {
        Helper::TestResult result;

        THeap heap;
        for (int i = 1; i <= TEST_PER_RUN_CNT; ++i)
        {
            result += insertion_test(heap);
        }
        result /= TEST_PER_RUN_CNT;
        std::ofstream insertion_file;
        insertion_file.open(m_insertion_path, std::ios_base::app);
        insertion_file << result << '\n';
        insertion_file.close();

        result = Helper::TestResult{};
        for (int i = 1; i <= TEST_PER_RUN_CNT; ++i)
        {
            result += deletion_test(heap);
        }
        result /= TEST_PER_RUN_CNT;
        std::ofstream deletion_file;
        deletion_file.open(m_deletion_path, std::ios_base::app);
        deletion_file << result << '\n';
        deletion_file.close();
    }

private:
    Helper::TestResult insertion_test(THeap& heap)
    {
        Helper::TestResult result;
        for (int i = 1; i <= m_size; ++i)
        {
            auto key = THeap::KeyT::generate();

            auto func = [&]() -> void
            {
                heap.push(key);
            };

            result += Helper::measure(func);
        }
        return result;
    }

    Helper::TestResult deletion_test(THeap& heap)
    {
        Helper::TestResult result;
        for (int i = 1; i <= m_size; ++i)
        {
            auto func = [&]() -> void
            {
                heap.pop();
            };

            result += Helper::measure(func);
        }
        return result;
    }

private:
    using ParentT::run;

    Helper::TestResult test()
    {
        return Helper::TestResult{};
    }

private:
    using ParentT::m_size;
    using ParentT::TEST_PER_RUN_CNT;

    std::filesystem::path m_insertion_path, m_deletion_path;
};
