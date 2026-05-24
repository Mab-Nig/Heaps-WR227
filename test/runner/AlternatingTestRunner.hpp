#pragma once

#include "AlternatingTestCaseRunner.hpp"
#include "Heap.hpp"
#include "TestRunner.hpp"

template <class THeap, class = std::enable_if_t<std::is_base_of_v<
                           Heap<typename THeap::KeyT>, THeap>>>
class AlternatingTestRunner : public TestRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = AlternatingTestRunner<THeap>;

public:
    using TestRunner::TestRunner;

private:
    Helper::TestResult run_test_case(std::ifstream& file_in,
                                     std::ofstream& file_out) override
    {
        AlternatingTestCaseRunner<THeap> runner(file_in, file_out);
        return runner();
    }
};
