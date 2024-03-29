#pragma once

#include "Graph.hpp"
#include "test/generator/TestCaseGenerator.hpp"

#include <fstream>
#include <random>

class GraphGenerator : public TestCaseGenerator
{
public:
    GraphGenerator(int vertex_cnt, int edge_cnt, std::ofstream& file);

    void operator()() override;

private:
    using AdjPair = Graph::AdjPair;
    using AdjList = Graph::AdjList;
    using AdjMatrix = Graph::AdjMatrix;
    using EdgeMap = Graph::EdgeMap;

private:
    void generate_mst(std::mt19937& gen);
    void generate_remaining(std::mt19937& gen);

private:
    static int constexpr WEIGHT_MAX = 1e9;

    using TestCaseGenerator::m_file;
    Graph m_graph;
    int& m_vertex_cnt = m_graph.m_vertex_cnt;
    int& m_edge_cnt = m_graph.m_edge_cnt;
    Graph::AdjMatrix& m_adj_matrix = m_graph.m_adj_matrix;
    Graph::EdgeMap& m_edge_map = m_graph.m_edge_map;
};
