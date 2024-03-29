#pragma once

#include "test/generator/Generator.hpp"

#include <fstream>

class TestCaseGenerator : public Generator
{
public:
    TestCaseGenerator(std::ofstream& file);

    void operator()() = 0;

protected:
    std::ofstream& m_file;
};
