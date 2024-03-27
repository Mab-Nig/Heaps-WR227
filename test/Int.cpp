#include "Int.hpp"

#include <random>

Int::Int(int value)
    : m_value(value)
{
}

Int Int::generate()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    Int result;
    result.m_value = gen();
    return result;
}

bool Int::operator<(Int const& other) const
{
    return m_value < other.m_value;
}

int Int::get() const
{
    return m_value;
}
