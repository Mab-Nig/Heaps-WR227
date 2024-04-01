#pragma once

#include "Graph.hpp"
#include "Helper.hpp"
#include "TestCaseRunner.hpp"

#include <climits>
#include <type_traits>
#include <vector>

template <class THeap, class = std::enable_if_t<std::is_same_v<
                           typename THeap::KeyT, std::pair<int64_t, int>>>>
class DijkstraTestCaseRunner : public TestCaseRunner
{
public:
    using HeapT = THeap;
    using DistancePair = std::pair<int64_t, int>;

public:
    using TestCaseRunner::TestCaseRunner;

    Helper::TestResult operator()() override
    {
        Graph graph;
        m_file_in >> graph;
        int vertex_cnt = graph.get_vertex_cnt();
        int edge_cnt = graph.get_edge_cnt();
        auto& adj_matrix = graph.get_adj_matrix();

        std::vector<int64_t> distances(vertex_cnt, LLONG_MAX);

        auto func = [&]() -> void
        {
            THeap heap;
            heap.emplace(0, 0);
            while (!heap.is_empty())
            {
                int64_t dist = heap.get_top().first;
                int vertex = heap.get_top().second;
                heap.pop();

                if (dist != distances[vertex])
                {
                    continue;
                }

                for (auto const& [w, v] : adj_matrix[vertex])
                {
                    if (dist + w >= distances[v])
                    {
                        continue;
                    }

                    distances[v] = dist + w;
                    heap.emplace(distances[v], v);
                }
            }
        };

        Helper::TestResult result = Helper::measure(func);

        for (auto dist : distances)
        {
            m_file_out << dist << ' ';
        }
        m_file_out << '\n';

        return result;
    }

private:
    using TestCaseRunner::m_file_in;
    using TestCaseRunner::m_file_out;
};
