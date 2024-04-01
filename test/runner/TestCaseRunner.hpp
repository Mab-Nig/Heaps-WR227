#pragma once

#include "Helper.hpp"

#include <fstream>

class TestCaseRunner
{
public:
    TestCaseRunner(std::ifstream& file_in, std::ofstream& file_out);

    virtual Helper::TestResult operator()() = 0;

protected:
    std::ifstream& m_file_in;
    std::ofstream& m_file_out;
};
