#include "BinaryHeap.hpp"
#include "BinomialHeap.hpp"
#include "Helper.hpp"
#include "PairingHeap.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int const N = 10000000;
std::vector<int> arr(N);

template <class THeap>
void test(THeap& heap)
{
    for (auto x : arr)
    {
        heap.push(x);
    }
    // while (!heap.is_empty())
    // {
    //     heap.pop();
    // }
}

template <class THeap>
void measure()
{
    THeap heap;
    auto binary_heap_test = [&]() -> void
    {
        test(heap);
    };
    Helper::measure(binary_heap_test);
    std::cout << '\n';
}

int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::iota(arr.begin(), arr.end(), 0);
    std::shuffle(arr.begin(), arr.end(), g);

    std::cout << "BINARY HEAP\n";
    measure<BinaryHeap<int>>();
    std::cout << "BINOMIAL HEAP\n";
    measure<BinomialHeap<int>>();
    std::cout << "PAIRING HEAP\n";
    measure<PairingHeap<int>>();
}
