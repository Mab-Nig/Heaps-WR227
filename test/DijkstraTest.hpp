#pragma once

#include "Dijkstra.hpp"
#include "Helper.hpp"
#include "test/Test.hpp"

#include <fstream>

template <class THeap>
class DijkstraTest : public Test<THeap>
{
public:
    using ParentT = Test<THeap>;
    using ParentT::HeapT;

public:
    using ParentT::Test;

private:
    Helper::TestResult test() override
    {
        Dijkstra dijkstra(m_size, m_size << 1);
        dijkstra.generate_graph();

        auto func = [&]() -> void
        {
            dijkstra.find_shortest_path<THeap>();
        };

        return Helper::measure(func);
    }

private:
    using ParentT::m_path;
    using ParentT::m_size;
    using ParentT::TEST_PER_RUN_CNT;
};
