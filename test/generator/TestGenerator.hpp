#pragma once

#include "test/generator/Generator.hpp"

#include <filesystem>
#include <fstream>

class TestGenerator : public Generator
{
public:
    TestGenerator(std::filesystem::path path);

    void operator()() override;

protected:
    virtual void generate_test_case(int magnitude_order,
                                    std::ofstream& file) = 0;

protected:
    static int constexpr MAGNITUDE_ORDER_MAX = 6;
    static int constexpr TEST_CASES_CNT = 10;

    std::filesystem::path m_path;
};
