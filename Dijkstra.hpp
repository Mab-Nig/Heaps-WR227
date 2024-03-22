#pragma once

#include <array>
#include <climits>
#include <map>
#include <random>
#include <type_traits>
#include <vector>

class Dijkstra
{
public:
    using DistancePair = std::pair<int64_t, int>;

public:
    Dijkstra(int vertex_cnt, int edge_cnt);

    void generate_graph();

    template <class THeap, class = std::enable_if_t<std::is_same_v<
                               typename THeap::KeyT, DistancePair>>>
    std::vector<int64_t> const& find_shortest_path()
    {
        m_distances.assign(m_vertex_cnt, LLONG_MAX);
        m_distances[0] = 0;
        THeap heap;
        heap.push({0, 0});
        while (!heap.is_empty())
        {
            DistancePair top = heap.get_top();
            heap.pop();
            int64_t weight = top.first;
            int vertex = top.second;

            if (weight != m_distances[vertex])
            {
                continue;
            }

            for (auto const& [w, v] : m_adjs[vertex])
            {
                if (weight + w >= m_distances[v])
                {
                    continue;
                }

                m_distances[v] = weight + w;
                heap.push(DistancePair{m_distances[v], v});
            }
        }
        return m_distances;
    }

private:
    using AdjPair = std::array<int, 2>;
    using AdjList = std::vector<AdjPair>;
    using AdjMatrix = std::vector<AdjList>;

private:
    std::map<std::array<int, 2>, bool> generate_mst(std::mt19937& generator);
    void generate_remaining_edges(std::map<AdjPair, bool> is_connected,
                                  std::mt19937& generator);

private:
    static int const WEIGHT_MAX = 1e9;

    int m_vertex_cnt, m_edge_cnt;
    AdjMatrix m_adjs;
    std::vector<int64_t> m_distances;
};
