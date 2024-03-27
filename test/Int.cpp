#include "Int.hpp"

#include <random>

Int Int::generate()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    return gen();
}

bool Int::operator<(Int const& other) const
{
    return m_value < other.m_value;
}

int Int::get() const
{
    return m_value;
}
