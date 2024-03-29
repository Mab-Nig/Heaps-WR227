#pragma once

#include <iostream>
#include <map>
#include <vector>

class GraphGenerator;

class Graph
{
public:
    struct AdjPair
    {
        int weight, vertex;
    };

    using AdjList = std::vector<AdjPair>;
    using AdjMatrix = std::vector<AdjList>;
    using EdgeMap = std::map<std::pair<int, int>, int>;

public:
    int get_vertex_cnt() const;
    int get_edge_cnt() const;
    AdjMatrix const& get_adj_matrix() const;

    friend std::istream& operator>>(std::istream& stream, Graph& instance);
    friend std::ostream& operator<<(std::ostream& stream,
                                    Graph const& instance);

private:
    int m_vertex_cnt, m_edge_cnt;
    AdjMatrix m_adj_matrix;
    EdgeMap m_edge_map;

private:
    friend class GraphGenerator;
};
