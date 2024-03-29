#pragma once

#include "test/generator/TestGenerator.hpp"

class DijkstraTestGenerator : public TestGenerator
{
public:
    using TestGenerator::TestGenerator;

private:
    void generate_test_case(int magnitude_order, std::ofstream& file) override;
};
