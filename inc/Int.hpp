#pragma once

#include <iostream>

class Int
{
public:
    static Int generate();

    Int(int value = 0);

    bool operator<(Int const& other) const;
    friend std::istream& operator>>(std::istream& stream, Int& instance);
    friend std::ostream& operator<<(std::ostream& stream, Int const& instance);

    int get() const;

private:
    int m_value;
};
