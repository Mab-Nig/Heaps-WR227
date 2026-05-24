#include "String.hpp"

#include <random>

String String::generate()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 25);

    std::string result(SIZE, 0);
    for (int i = 0; i < SIZE; ++i)
    {
        result[i] = 'a' + dist(gen);
    }
    return result;
}

String::String(std::string const& value)
    : m_value{value}
{
}

String::String(std::string&& value)
    : m_value{std::move(value)}
{
}

std::istream& operator>>(std::istream& stream, String& instance)
{
    stream >> instance.m_value;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, String const& instance)
{
    stream << instance.m_value;
    return stream;
}

bool String::operator<(String const& other) const
{
    return m_value < other.m_value;
}

std::string const& String::get() const
{
    return m_value;
}
