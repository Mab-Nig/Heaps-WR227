#pragma once

#include "test/generator/TestCaseGenerator.hpp"
#include "vec_utils.hpp"

#include <fstream>
#include <vector>

template <class TKey>
class SequenceGenerator : public TestCaseGenerator
{
public:
    using SelfT = SequenceGenerator<TKey>;
    using KeyT = TKey;

public:
    SequenceGenerator(int size, std::ofstream& file)
        : TestCaseGenerator(file),
          m_size(size)
    {
    }

    void operator()() override
    {
        std::vector<TKey> result(m_size);
        for (int i = 0; i < m_size; ++i)
        {
            result[i] = TKey::generate();
        }

        m_file << result;
    }

private:
    using TestCaseGenerator::m_file;
    int m_size;
};
