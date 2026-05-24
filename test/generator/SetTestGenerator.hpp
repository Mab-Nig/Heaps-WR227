#pragma once

#include "SetTestCaseGenerator.hpp"
#include "TestGenerator.hpp"

#include <cmath>

template <class TKey>
class SetTestGenerator : public TestGenerator
{
public:
    using SelfT = SetTestGenerator<TKey>;
    using KeyT = TKey;

public:
    using TestGenerator::TestGenerator;

private:
    void generate_test_case(int magnitude_order, std::ofstream& file) override
    {
        int size = std::pow(10, magnitude_order);
        SetTestCaseGenerator<TKey> generator(size, file);
        generator();
    }
};
