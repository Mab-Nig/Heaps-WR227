#include "AllHeap.hpp"
#include "Dijkstra.hpp"
#include "HeapSort.hpp"

template <class THeap>
void measure()
{
    int const N = 10000;
    int const M = 30000;
    Dijkstra dijkstra(N, M);
    dijkstra.generate_graph();
    auto measure = [&]() -> void
    {
        dijkstra.find_shortest_path<PairingHeap<std::pair<int64_t, int>>>();
    };
    Helper::measure(measure);
}

int main()
{
    measure<BinaryHeap<std::pair<int64_t, int>>>();
}
