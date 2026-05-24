#pragma once

#include <iostream>
#include <string>

class String
{
public:
    static String generate();

    String() = default;
    String(std::string const& value);
    String(std::string&& value);

    bool operator<(String const& other) const;
    friend std::istream& operator>>(std::istream& stream, String& instance);
    friend std::ostream& operator<<(std::ostream& stream,
                                    String const& instance);

    std::string const& get() const;

private:
    static int constexpr SIZE = 20;

    std::string m_value;
};
