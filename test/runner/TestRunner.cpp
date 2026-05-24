#include "TestRunner.hpp"

#include "Helper.hpp"
#include "test/paths.hpp"

#include <iostream>

TestRunner::TestRunner(std::filesystem::path input_path,
                       std::filesystem::path output_path,
                       std::filesystem::path measurement_path)
    : m_input_path(input_path),
      m_output_path(output_path),
      m_measurement_path(measurement_path)
{
}

void TestRunner::operator()()
{
    namespace fs = std::filesystem;

    fs::create_directories(m_output_path);
    fs::create_directories(m_measurement_path);

    ResultFiles files(m_measurement_path);

    for (auto const& dir_entry : fs::directory_iterator(m_input_path))
    {
        int magnitude_order = std::stoi(dir_entry.path().stem());

        std::ifstream file_in(dir_entry.path());
        std::ofstream file_out(m_output_path / dir_entry.path().filename());

        int test_case_cnt;
        file_in >> test_case_cnt;
        Helper::TestResult result;
        for (int i = 1; i <= test_case_cnt; ++i)
        {
            result += run_test_case(file_in, file_out);
        }
        result /= test_case_cnt;

        files.write(magnitude_order, result);
    }
}

TestRunner::ResultFiles::ResultFiles(std::filesystem::path prefix)
    : time(TestRunner::stem_to_path(tpaths::TIME, prefix)),
      comparison_cnt(TestRunner::stem_to_path(tpaths::COMPARISON_CNT, prefix)),
      swap_cnt(TestRunner::stem_to_path(tpaths::SWAP_CNT, prefix)),
      iteration_cnt(TestRunner::stem_to_path(tpaths::ITERATION_CNT, prefix))
{
}

void TestRunner::ResultFiles::write(int magnitude_order,
                                    Helper::TestResult const& test_result)
{
    time << magnitude_order << ' ' << test_result.time << '\n';
    comparison_cnt << magnitude_order << ' ' << test_result.comparison_cnt
                   << '\n';
    swap_cnt << magnitude_order << ' ' << test_result.swap_cnt << '\n';
    iteration_cnt << magnitude_order << ' ' << test_result.iteration_cnt
                  << '\n';
}

std::filesystem::path TestRunner::stem_to_path(std::filesystem::path stem,
                                               std::filesystem::path prefix)
{
    namespace fs = std::filesystem;

    fs::path result = prefix;
    result /= stem;
    result += ".txt";
    return result;
}

std::filesystem::path TestRunner::stem_to_path(std::filesystem::path stem) const
{
    return TestRunner::stem_to_path(stem, m_measurement_path);
}
