#include "TestRunner.hpp"

#include "Helper.hpp"
#include "test/paths.hpp"

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

    auto stem_to_path = [&](fs::path stem) -> fs::path
    {
        fs::path result = m_measurement_path;
        result /= stem;
        result += ".txt";
        return result;
    };

    std::ofstream file_time(stem_to_path(tpaths::TIME));
    std::ofstream file_comparison_cnt(stem_to_path(tpaths::COMPARISON_CNT));
    std::ofstream file_swap_cnt(stem_to_path(tpaths::SWAP_CNT));
    std::ofstream file_iteration_cnt(stem_to_path(tpaths::ITERATION_CNT));

    for (auto const& dir_entry : fs::directory_iterator(m_input_path))
    {
        int magnitude_order = std::stoi(m_output_path.stem());

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

        file_time << magnitude_order << ' ' << result.time << '\n';
        file_comparison_cnt << magnitude_order << ' ' << result.comparison_cnt
                            << '\n';
        file_swap_cnt << magnitude_order << ' ' << result.swap_cnt << '\n';
        file_iteration_cnt << magnitude_order << ' ' << result.iteration_cnt
                           << '\n';
    }
}
