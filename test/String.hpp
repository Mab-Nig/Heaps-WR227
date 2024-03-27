#pragma once

#include <string>
#include <string_view>

class String
{
public:
    static String generate();

    String(std::string_view value);

    bool operator<(String const& other) const;
    std::string const& get() const;

private:
    static int constexpr SIZE = 20;

    std::string m_value;
};
