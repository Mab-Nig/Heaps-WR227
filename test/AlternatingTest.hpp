#pragma once

template <class THeap>
class AlternatingTest
{
public:
    using HeapT = THeap;
    using SelfT = AlternatingTest<THeap>;

public:
    AlternatingTest(int size)
        : m_size(size)
    {
    }

private:
    static int const TEST_PER_RUN_CNT = 40;

    int m_size;
};
