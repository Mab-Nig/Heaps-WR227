#include "TestGenerator.hpp"

#include <iostream>
#include <string>

TestGenerator::TestGenerator(std::filesystem::path path)
    : m_path(path)
{
}

void TestGenerator::operator()()
{
    std::filesystem::create_directories(m_path);
    for (int i = 1; i <= MAGNITUDE_ORDER_MAX; ++i)
    {
        std::string filename = std::to_string(i) + ".txt";
        std::ofstream file(m_path / filename);
        file << TEST_CASES_CNT << '\n';
        for (int j = 1; j <= TEST_CASES_CNT; ++j)
        {
            generate_test_case(i, file);
        }
    }
}
