#pragma once

#include "BinaryHeap.hpp"
#include "BinomialHeap.hpp"
#include "PairingHeap.hpp"
#include "test/AlternatingTest.hpp"
#include "test/DijkstraTest.hpp"
#include "test/HeapSortTest.hpp"
#include "test/SequentialTest.hpp"

#include <cmath>
#include <filesystem>
#include <type_traits>

class TestSystem
{
public:
    void run();

private:
    template <class TKey>
    void type_run(std::filesystem::path path)
    {
        heap_run<BinaryHeap<TKey>>(path / BINARY_HEAP);
        heap_run<BinomialHeap<TKey>>(path / BINOMIAL_HEAP);
        heap_run<PairingHeap<TKey>>(path / PAIRING_HEAP);
    }

    template <class THeap>
    void dijkstra_run(std::filesystem::path path)
    {
        path += ".txt";
        std::filesystem::create_directories(path.parent_path());
        for (int degree = 1; degree <= DEGREE_MAX; ++degree)
        {
            int size = std::pow(10, degree);
            DijkstraTest<THeap> test(size, path);
            test.run();
        }
    }

    template <class THeap>
    void heap_run(std::filesystem::path path)
    {
        test_run<AlternatingTest<THeap>>(path / ALTERNATING_TEST);
        test_run<HeapSortTest<THeap>>(path / HEAP_SORT_TEST);
        test_run<SequentialTest<THeap>>(path / INSERTION_ONLY,
                                        path / DELETION_ONLY);
    }

    template <class TTest>
    void test_run(std::filesystem::path path)
    {
        path += ".txt";
        std::filesystem::create_directories(path.parent_path());
        for (int degree = 1; degree <= DEGREE_MAX; ++degree)
        {
            int size = std::pow(10, degree);
            TTest test(size, path);
            test.run();
        }
    }

    template <class TTest, class = std::enable_if_t<std::is_same_v<
                               TTest, SequentialTest<typename TTest::HeapT>>>>
    void test_run(std::filesystem::path insertion_path,
                  std::filesystem::path deletion_path)
    {
        insertion_path += ".txt";
        deletion_path += ".txt";
        std::filesystem::create_directories(insertion_path.parent_path());
        std::filesystem::create_directories(deletion_path.parent_path());
        for (int degree = 1; degree <= DEGREE_MAX; ++degree)
        {
            int size = std::pow(10, degree);
            TTest test(size, insertion_path, deletion_path);
            test.run();
        }
    }

private:
    static int constexpr DEGREE_MAX = 6;

    static std::filesystem::path const TEST_RESULTS_FOLDER;

    static std::filesystem::path const LIGHT_DATA_TYPE;
    static std::filesystem::path const HEAVY_DATA_TYPE;
    static std::filesystem::path const DIJKSTRA_TEST;

    static std::filesystem::path const BINARY_HEAP;
    static std::filesystem::path const BINOMIAL_HEAP;
    static std::filesystem::path const PAIRING_HEAP;

    static std::filesystem::path const ALTERNATING_TEST;
    static std::filesystem::path const HEAP_SORT_TEST;
    static std::filesystem::path const INSERTION_ONLY;
    static std::filesystem::path const DELETION_ONLY;
};
