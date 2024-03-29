#include "GraphGenerator.hpp"

GraphGenerator::GraphGenerator(int vertex_cnt, int edge_cnt,
                               std::ofstream& file)
    : TestCaseGenerator(file)
{
    m_vertex_cnt = vertex_cnt;
    m_edge_cnt = edge_cnt;
}

void GraphGenerator::operator()()
{
    m_adj_matrix.assign(m_vertex_cnt, AdjList{});
    m_edge_map.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    generate_mst(gen);
    generate_remaining(gen);

    m_file << m_graph;
}

void GraphGenerator::generate_mst(std::mt19937& gen)
{
    std::vector<int> parents(m_vertex_cnt);
    for (int i = 1; i < m_vertex_cnt; ++i)
    {
        parents[i] = gen() % i;
        int weight = gen() % WEIGHT_MAX;

        m_adj_matrix[i].emplace_back(weight, parents[i]);
        m_adj_matrix[parents[i]].emplace_back(weight, i);

        m_edge_map.emplace(std::make_pair(i, parents[i]), weight);
    }
}

void GraphGenerator::generate_remaining(std::mt19937& gen)
{
    std::uniform_int_distribution<> dist(0, m_vertex_cnt - 1);
    for (int i = 1; i <= m_edge_cnt - m_vertex_cnt + 1; ++i)
    {
        int u, v;
        int weight = gen() % WEIGHT_MAX;
        do
        {
            u = dist(gen);
            v = dist(gen);
        } while (u == v || m_edge_map.count(std::make_pair(u, v))
                 || m_edge_map.count(std::make_pair(v, u)));

        m_adj_matrix[u].emplace_back(weight, v);
        m_adj_matrix[v].emplace_back(weight, u);

        m_edge_map.emplace(std::make_pair(u, v), weight);
    }
}
