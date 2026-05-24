#include "Int.hpp"

#include <random>

Int Int::generate()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    return gen();
}

Int::Int(int value)
    : m_value(value)
{
}

bool Int::operator<(Int const& other) const
{
    return m_value < other.m_value;
}

std::istream& operator>>(std::istream& stream, Int& instance)
{
    stream >> instance.m_value;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Int const& instance)
{
    stream << instance.m_value;
    return stream;
}

int Int::get() const
{
    return m_value;
}
