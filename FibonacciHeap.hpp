#pragma once

template <class TKey, class TCompare>
class FibonacciHeap
{
public:
    using HeapT = FibonacciHeap<TKey, TCompare>;

public:
    FibonacciHeap() = default;

    FibonacciHeap(HeapT const&) = delete;

    HeapT& operator=(HeapT const&) = delete;

private:
    int m_size = 0;
};
