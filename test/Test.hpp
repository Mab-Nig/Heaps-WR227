#pragma once

#include "Helper.hpp"

#include <filesystem>
#include <fstream>

template <class THeap>
class Test
{
public:
    using HeapT = THeap;

public:
    Test() = default;

    Test(int size, std::filesystem::path path)
        : m_size(size),
          m_path(path)
    {
    }

    virtual ~Test() = default;

    virtual void run()
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

protected:
    virtual Helper::TestResult test() = 0;

protected:
    static int constexpr TEST_PER_RUN_CNT = 40;

    int m_size;
    std::filesystem::path m_path;
};
