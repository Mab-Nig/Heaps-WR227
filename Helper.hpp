#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>

class Helper
{
public:
    static int64_t get_swap_cnt();
    static int64_t get_comparison_cnt();
    static int64_t get_iteration_cnt();
    static void increase_iteration_cnt();
    static void reset();

    template <class T, class U>
    static void swap(T& a, U& b)
    {
        ++Helper::swap_cnt;
        std::swap(a, b);
    }

    template <class TKey, class TCompare>
    static bool compare(TKey const& a, TKey const& b, TCompare compare)
    {
        ++Helper::comparison_cnt;
        return compare(a, b);
    }

    static void measure(std::function<void()> func);

private:
    static int64_t swap_cnt;
    static int64_t comparison_cnt;
    static int64_t iteration_cnt;
};
