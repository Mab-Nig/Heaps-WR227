#pragma once

#include "DijkstraTestCaseRunner.hpp"
#include "Helper.hpp"
#include "TestRunner.hpp"

template <class THeap>
class DijkstraTestRunner : public TestRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;

public:
    using TestRunner::TestRunner;

private:
    Helper::TestResult run_test_case(std::ifstream& file_in,
                                     std::ofstream& file_out) override
    {
        DijkstraTestCaseRunner<THeap> dijkstra_test_case_runner(file_in,
                                                                file_out);
        return dijkstra_test_case_runner();
    }
};
