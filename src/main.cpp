#include "AllGenerator.hpp"
#include "AllHeap.hpp"
#include "AllTestRunner.hpp"
#include "Int.hpp"
#include "String.hpp"
#include "test/paths.hpp"

int main()
{
    namespace fs = std::filesystem;
    using DistancePair = std::pair<int64_t, int>;
    using namespace tpaths;

    DijkstraTestRunner<PairingHeap<DistancePair, std::greater<DistancePair>>>
        runner(fs::path(TEST) / INPUT / GRAPH,
               fs::path(TEST) / OUTPUT / DIJKSTRA / PAIRING_HEAP,
               fs::path(TEST) / MEASUREMENT / DIJKSTRA / PAIRING_HEAP);
    runner();

    // MeldTestRunner<BinaryHeap<std::string>> binary_runner(
    //     fs::path(TEST) / INPUT / SET / HEAVY_TYPE,
    //     fs::path(TEST) / OUTPUT / HEAVY_TYPE / MELD / BINARY_HEAP,
    //     fs::path(TEST) / MEASUREMENT / HEAVY_TYPE / MELD / BINARY_HEAP);
    // binary_runner();

    // MeldTestRunner<BinomialHeap<std::string>> binomial_runner(
    //     fs::path(TEST) / INPUT / SET / HEAVY_TYPE,
    //     fs::path(TEST) / OUTPUT / HEAVY_TYPE / MELD / BINOMIAL_HEAP,
    //     fs::path(TEST) / MEASUREMENT / HEAVY_TYPE / MELD / BINOMIAL_HEAP);
    // binomial_runner();

    // MeldTestRunner<PairingHeap<std::string>> pairing_runner(
    //     fs::path(TEST) / INPUT / SET / HEAVY_TYPE,
    //     fs::path(TEST) / OUTPUT / HEAVY_TYPE / MELD / PAIRING_HEAP,
    //     fs::path(TEST) / MEASUREMENT / HEAVY_TYPE / MELD / PAIRING_HEAP);
    // pairing_runner();
}
