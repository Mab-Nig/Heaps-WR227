#pragma once

#include "Helper.hpp"

#include <filesystem>
#include <fstream>

class TestRunner
{
public:
    TestRunner(std::filesystem::path input_path,
               std::filesystem::path output_path,
               std::filesystem::path measurement_path);

    void operator()();

protected:
    virtual Helper::TestResult run_test_case(std::ifstream& file_in,
                                             std::ofstream& file_out) = 0;

protected:
    std::filesystem::path m_input_path, m_output_path, m_measurement_path;
};
