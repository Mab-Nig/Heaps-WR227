#include "Helper.hpp"

int64_t Helper::swap_cnt;
int64_t Helper::comparison_cnt;
int64_t Helper::iteration_cnt;

int64_t Helper::get_swap_cnt()
{
    return Helper::swap_cnt;
}

int64_t Helper::get_comparison_cnt()
{
    return Helper::comparison_cnt;
}

int64_t Helper::get_iteration_cnt()
{
    return Helper::iteration_cnt;
}

void Helper::increase_iteration_cnt()
{
    ++Helper::iteration_cnt;
}

void Helper::reset()
{
    Helper::swap_cnt = Helper::comparison_cnt = Helper::iteration_cnt = 0;
}

void Helper::measure(std::function<void()> func)
{
    using namespace std::chrono;

    Helper::reset();
    auto begin = steady_clock::now();
    func();
    auto end = steady_clock::now();

    int64_t time = duration_cast<milliseconds>(end - begin).count();
    std::cout.imbue(std::locale(""));
    std::cout << "Number of comparisons: " << Helper::comparison_cnt << '\n';
    std::cout << "Number of swaps: " << Helper::swap_cnt << '\n';
    std::cout << "Number of iterations: " << Helper::iteration_cnt << '\n';
    std::cout << "Execution time: " << time << "ms\n";
}
