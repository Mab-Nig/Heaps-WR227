#include "Graph.hpp"

int Graph::get_vertex_cnt() const
{
    return m_vertex_cnt;
}

int Graph::get_edge_cnt() const
{
    return m_edge_cnt;
}

Graph::AdjMatrix const& Graph::get_adj_matrix() const
{
    return m_adj_matrix;
}

std::istream& operator>>(std::istream& stream, Graph& instance)
{
    stream >> instance.m_vertex_cnt >> instance.m_edge_cnt;
    instance.m_adj_matrix.assign(instance.m_vertex_cnt, Graph::AdjList{});
    for (int i = 0; i < instance.m_edge_cnt; ++i)
    {
        int u, v, w;
        stream >> u >> v >> w;

        instance.m_adj_matrix[u].emplace_back(w, v);
        instance.m_adj_matrix[v].emplace_back(w, u);

        instance.m_edge_map.emplace(std::make_pair(u, v), w);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Graph const& instance)
{
    stream << instance.m_vertex_cnt << ' ' << instance.m_edge_cnt << '\n';
    for (auto const& [pair, w] : instance.m_edge_map)
    {
        stream << pair.first << ' ' << pair.second << ' ' << w << '\n';
    }
    return stream;
}
