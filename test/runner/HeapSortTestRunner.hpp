#pragma once

#include "HeapSortTestCaseRunner.hpp"
#include "Helper.hpp"
#include "TestRunner.hpp"

template <class THeap>
class HeapSortTestRunner : public TestRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = HeapSortTestRunner<THeap>;

public:
    using TestRunner::TestRunner;

private:
    Helper::TestResult run_test_case(std::ifstream& file_in,
                                     std::ofstream& file_out) override
    {
        HeapSortTestCaseRunner<THeap> heap_sort_test_case_runner(file_in,
                                                                 file_out);
        return heap_sort_test_case_runner();
    }
};
