#include "AllHeap.hpp"
#include "AllTestRunner.hpp"
#include "test/paths.hpp"

int main()
{
    namespace fs = std::filesystem;
    using DistancePair = std::pair<int64_t, int>;
    using namespace tpaths;

    DijkstraTestRunner<BinaryHeap<DistancePair>> runner(
        fs::path(TEST) / INPUT / GRAPH,
        fs::path(TEST) / OUTPUT / DIJKSTRA / BINARY_HEAP,
        fs::path(TEST) / MEASUREMENT / DIJKSTRA / BINARY_HEAP);
    runner();
}
