#pragma once

#include "test/generator/SequenceGenerator.hpp"
#include "test/generator/TestGenerator.hpp"

#include <cmath>

template <class TKey>
class HeapSortTestGenerator : public TestGenerator
{
public:
    using TestGenerator::TestGenerator;

private:
    void generate_test_case(int magnitude_order, std::ofstream& file) override
    {
        int size = std::pow(10, magnitude_order);
        SequenceGenerator<TKey> sequence_generator(size, file);
        sequence_generator();
    }
};
