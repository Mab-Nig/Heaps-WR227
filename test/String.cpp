#include "String.hpp"

#include <random>

String String::generate()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist;
    std::string result;
    result.resize(SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        result[i] = dist(gen);
    }
    return std::string_view(result);
}

String::String(std::string_view value)
    : m_value(value)
{
}

bool String::operator<(String const& other) const
{
    return m_value < other.m_value;
}

std::string const& String::get() const
{
    return m_value;
}
