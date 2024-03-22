#include "Dijkstra.hpp"

Dijkstra::Dijkstra(int vertex_cnt, int edge_cnt)
    : m_vertex_cnt(vertex_cnt),
      m_edge_cnt(edge_cnt)
{
}

void Dijkstra::generate_graph()
{
    m_adjs.assign(m_vertex_cnt, AdjList());
    m_distances.resize(m_vertex_cnt);
    std::random_device rd;
    std::mt19937 gen(rd());
    generate_remaining_edges(generate_mst(gen), gen);
}

std::map<Dijkstra::AdjPair, bool>
Dijkstra::generate_mst(std::mt19937& generator)
{
    std::vector<AdjPair> parents(m_vertex_cnt);
    for (int i = 1; i < m_vertex_cnt; ++i)
    {
        parents[i][0] = generator() % WEIGHT_MAX;
        parents[i][1] = generator() % i;
    }
    std::map<AdjPair, bool> is_connected;
    for (int i = 1; i < m_vertex_cnt; ++i)
    {
        is_connected.emplace(AdjPair{i, parents[i][1]}, 1);
        is_connected.emplace(AdjPair{parents[i][1], i}, 1);
        m_adjs[i].push_back(parents[i]);
        m_adjs[parents[i][1]].push_back(AdjPair{parents[i][0], i});
    }
    return is_connected;
}

void Dijkstra::generate_remaining_edges(
    std::map<Dijkstra::AdjPair, bool> is_connected, std::mt19937& generator)
{
    for (int i = 1; i <= m_edge_cnt - m_vertex_cnt + 1; ++i)
    {
        int u = generator() % m_vertex_cnt;
        int v;
        do
        {
            v = generator() % m_vertex_cnt;
        } while (v == u || is_connected[{u, v}]);
        is_connected.emplace(AdjPair{u, v}, 1);
        is_connected.emplace(AdjPair{v, u}, 1);

        int w = generator() % WEIGHT_MAX;
        m_adjs[u].push_back(AdjPair{w, v});
        m_adjs[v].push_back(AdjPair{w, u});
    }
}
