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
    virtual ~TestRunner() = default;

    virtual void operator()();

protected:
    struct ResultFiles
    {
        std::ofstream time, comparison_cnt, swap_cnt, iteration_cnt;

        ResultFiles(std::filesystem::path prefix);
        void write(int magnitude_order, Helper::TestResult const& test_result);
    };

protected:
    static std::filesystem::path stem_to_path(std::filesystem::path stem,
                                              std::filesystem::path prefix);

    virtual Helper::TestResult run_test_case(std::ifstream& file_in,
                                             std::ofstream& file_out) = 0;

protected:
    std::filesystem::path m_input_path, m_output_path, m_measurement_path;

private:
    std::filesystem::path stem_to_path(std::filesystem::path stem) const;
};
