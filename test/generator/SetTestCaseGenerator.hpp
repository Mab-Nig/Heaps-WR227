#pragma once

#include "SequenceGenerator.hpp"
#include "TestCaseGenerator.hpp"

template <class TKey>
class SetTestCaseGenerator : public TestCaseGenerator
{
public:
    using SelfT = SetTestCaseGenerator<TKey>;
    using KeyT = TKey;

public:
    SetTestCaseGenerator(int size, std::ofstream& file)
        : TestCaseGenerator(file),
          m_size(size)
    {
    }

    void operator()() override
    {
        m_file << m_size << '\n';
        for (int i = 1; i <= m_size; ++i)
        {
            SequenceGenerator<TKey> sequence_generator(SEQUENCE_SIZE, m_file);
            sequence_generator();
        }
    }

private:
    static int constexpr SEQUENCE_SIZE = 10;

    using TestCaseGenerator::m_file;
    int m_size;
};
