#pragma once

#include "Heap.hpp"
#include "MeldTestCaseRunner.hpp"
#include "TestRunner.hpp"

#include <type_traits>

template <class THeap, class = std::enable_if_t<std::is_base_of_v<
                           Heap<typename THeap::KeyT>, THeap>>>
class MeldTestRunner : public TestRunner
{
public:
    using HeapT = THeap;
    using KeyT = typename THeap::KeyT;
    using SelfT = MeldTestRunner<THeap>;

public:
    using TestRunner::TestRunner;

private:
    Helper::TestResult run_test_case(std::ifstream& file_in,
                                     std::ofstream& file_out) override
    {
        MeldTestCaseRunner<THeap> runner(file_in, file_out);
        return runner();
    }
};
