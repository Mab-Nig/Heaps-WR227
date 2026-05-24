#include "Helper.hpp"

#include <chrono>
#include <cmath>

int64_t Helper::swap_cnt;
int64_t Helper::comparison_cnt;
int64_t Helper::iteration_cnt;

Helper::TestResult&
Helper::TestResult::operator+=(Helper::TestResult const& other)
{
    time += other.time;
    comparison_cnt += other.comparison_cnt;
    swap_cnt += other.swap_cnt;
    iteration_cnt += other.iteration_cnt;
    return *this;
}

Helper::TestResult& Helper::TestResult::operator/=(int x)
{
    time = std::round(1.0 * time / x);
    comparison_cnt = std::round(1.0 * comparison_cnt / x);
    swap_cnt = std::round(1.0 * swap_cnt / x);
    iteration_cnt = std::round(1.0 * iteration_cnt / x);
    return *this;
}

std::ostream& operator<<(std::ostream& stream,
                         Helper::TestResult const& instance)
{
    stream << instance.time << ' ' << instance.comparison_cnt << ' '
           << instance.swap_cnt << ' ' << instance.swap_cnt;
    return stream;
}

int64_t Helper::get_comparison_cnt()
{
    return Helper::comparison_cnt;
}

int64_t Helper::get_swap_cnt()
{
    return Helper::swap_cnt;
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

Helper::TestResult Helper::measure(std::function<void()> func)
{
    using namespace std::chrono;

    Helper::reset();
    auto begin = steady_clock::now();
    func();
    auto end = steady_clock::now();

    TestResult result;
    result.time = duration_cast<milliseconds>(end - begin).count();
    result.comparison_cnt = Helper::comparison_cnt;
    result.swap_cnt = Helper::swap_cnt;
    result.iteration_cnt = Helper::iteration_cnt;
    return result;
}
