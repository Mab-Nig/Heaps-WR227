#include "Int.hpp"
#include "String.hpp"
#include "test/generator/DijkstraTestGenerator.hpp"
#include "test/generator/HeapSortGenerator.hpp"
#include "test/paths.hpp"

#include <filesystem>

int main()
{
    namespace fs = std::filesystem;
    // DijkstraTestGenerator dijkstra_test_generator(
    //     fs::path(tpaths::TEST) / tpaths::INPUT / tpaths::DIJKSTRA);
    // dijkstra_test_generator();
    HeapSortTestGenerator<String> heap_sort_test_generator(
        fs::path(tpaths::TEST) / tpaths::INPUT / tpaths::HEAVY_TYPE);
    heap_sort_test_generator();
}
