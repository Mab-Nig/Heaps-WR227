#pragma once

class Int
{
public:
    static Int generate();

    Int() = default;
    Int(int value);

    bool operator<(Int const& other) const;
    int get() const;

private:
    int m_value;
};
