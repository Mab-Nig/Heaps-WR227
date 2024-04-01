#pragma once

#include <iostream>
#include <vector>

template <class TKey>
std::istream& operator>>(std::istream& stream, std::vector<TKey>& vec)
{
    int size;
    stream >> size;
    vec.resize(size);
    for (auto& key : vec)
    {
        stream >> key;
    }
    return stream;
}

template <class TKey>
std::ostream& operator<<(std::ostream& stream, std::vector<TKey> const& vec)
{
    stream << vec.size() << '\n';
    for (auto const& key : vec)
    {
        stream << key << ' ';
    }
    stream << '\n';
    return stream;
}
