#include "TestCaseRunner.hpp"

TestCaseRunner::TestCaseRunner(std::ifstream& file_in, std::ofstream& file_out)
    : m_file_in(file_in),
      m_file_out(file_out)
{
}
