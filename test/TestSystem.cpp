#include "TestSystem.hpp"

#include "BinaryHeap.hpp"
#include "Dijkstra.hpp"
#include "Int.hpp"
#include "String.hpp"

#include <filesystem>

namespace fs = std::filesystem;

fs::path const TestSystem::TEST_RESULTS_FOLDER = "test/results";

fs::path const TestSystem::LIGHT_DATA_TYPE = "light_data_type";
fs::path const TestSystem::HEAVY_DATA_TYPE = "heavy_data_type";
fs::path const TestSystem::DIJKSTRA_TEST = "dijkstra_test";

fs::path const TestSystem::BINARY_HEAP = "binary_heap";
fs::path const TestSystem::BINOMIAL_HEAP = "binomial_heap";
fs::path const TestSystem::PAIRING_HEAP = "pairing_heap";

fs::path const TestSystem::ALTERNATING_TEST = "alternating_test";
fs::path const TestSystem::HEAP_SORT_TEST = "heap_sort_test";
fs::path const TestSystem::INSERTION_ONLY = "insertion_only";
fs::path const TestSystem::DELETION_ONLY = "deletion_only";

void TestSystem::run()
{
    // fs::remove_all(TEST_RESULTS_FOLDER);

    // type_run<Int>(TEST_RESULTS_FOLDER / LIGHT_DATA_TYPE);
    // type_run<String>(TEST_RESULTS_FOLDER / HEAVY_DATA_TYPE);

    // dijkstra_run<BinaryHeap<Dijkstra::DistancePair,
    //                         std::greater<Dijkstra::DistancePair>>>(
    //     TEST_RESULTS_FOLDER / DIJKSTRA_TEST / BINARY_HEAP);
    // dijkstra_run<BinomialHeap<Dijkstra::DistancePair,
    //                           std::greater<Dijkstra::DistancePair>>>(
    //     TEST_RESULTS_FOLDER / DIJKSTRA_TEST / BINOMIAL_HEAP);
    dijkstra_run<PairingHeap<Dijkstra::DistancePair,
                             std::greater<Dijkstra::DistancePair>>>(
        TEST_RESULTS_FOLDER / DIJKSTRA_TEST / PAIRING_HEAP);
}
