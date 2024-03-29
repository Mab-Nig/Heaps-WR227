#include "DijkstraTestGenerator.hpp"

#include "test/generator/GraphGenerator.hpp"

#include <cmath>

void DijkstraTestGenerator::generate_test_case(int magnitude_order,
                                               std::ofstream& file)
{
    int vertex_cnt = std::pow(10, magnitude_order);
    int edge_cnt = vertex_cnt << 1;
    GraphGenerator dijkstra_generator(vertex_cnt, edge_cnt, file);
    dijkstra_generator();
}
