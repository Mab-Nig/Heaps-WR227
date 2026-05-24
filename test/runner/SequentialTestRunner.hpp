#pragma once

#include "Heap.hpp"
#include "Helper.hpp"
#include "SequentialTestCaseRunner.hpp"
#include "TestRunner.hpp"
#include "test/paths.hpp"

#include <filesystem>
#include <fstream>
#include <string>

template <class THeap, class = std::enable_if_t<std::is_base_of_v<
                           Heap<typename THeap::KeyT>, THeap>>>
class SequentialTestRunner : public TestRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = SequentialTestRunner<THeap>;

public:
    SequentialTestRunner(std::filesystem::path input_path,
                         std::filesystem::path output_path,
                         std::filesystem::path insertion_only_path,
                         std::filesystem::path deletion_only_path)
        : TestRunner(input_path, output_path, insertion_only_path),
          m_deletion_only_path(deletion_only_path)
    {
    }

    void operator()() override
    {
        namespace fs = std::filesystem;

        fs::create_directories(m_output_path);
        fs::create_directories(m_insertion_only_path);
        fs::create_directories(m_deletion_only_path);

        TestRunner::ResultFiles insertion_only_files(m_insertion_only_path);
        TestRunner::ResultFiles deletion_only_files(m_deletion_only_path);

        for (auto const& dir_entry : fs::directory_iterator(m_input_path))
        {
            int magnitude_order = std::stoi(dir_entry.path().stem());

            std::ifstream file_in(dir_entry.path());
            std::ofstream file_out(m_output_path / dir_entry.path().filename());

            int test_case_cnt;
            file_in >> test_case_cnt;
            Helper::TestResult insertion_only_result, deletion_only_result;
            for (int i = 1; i <= test_case_cnt; ++i)
            {
                SequentialTestCaseRunner<THeap> runner(file_in, file_out);
                insertion_only_result += runner();
                deletion_only_result += runner.get_deletion_only_result();
            }
            insertion_only_result /= test_case_cnt;
            deletion_only_result /= test_case_cnt;

            insertion_only_files.write(magnitude_order, insertion_only_result);
            deletion_only_files.write(magnitude_order, deletion_only_result);
        }
    }

private:
    [[deprecated]]
    Helper::TestResult run_test_case(std::ifstream& file_in,
                                     std::ofstream& file_out) override
    {
        return Helper::TestResult();
    }

private:
    using TestRunner::m_input_path;
    using TestRunner::m_output_path;
    std::filesystem::path& m_insertion_only_path =
        TestRunner::m_measurement_path;
    std::filesystem::path m_deletion_only_path;
};
