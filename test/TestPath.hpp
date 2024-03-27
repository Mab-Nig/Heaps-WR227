#pragma once

#include <filesystem>

namespace TEST_PATH
{
namespace fs = std::filesystem;

fs::path const TEST;

fs::path const INPUT;
fs::path const OUTPUT;

fs::path const BINARY_HEAP;
fs::path const BINOMIAL_HEAP;
fs::path const PAIRING_HEAP;

fs::path const ALTERNATING;
fs::path const INSERTION_ONLY;
fs::path const DELETION_ONLY;
}; // namespace TEST_PATH
