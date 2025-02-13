#pragma once
#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"

#include <vector>
#include <sstream>

namespace cse_test_utils
{
  double const FLOAT_DELTA = 0.000001;

  bool CheckForStringFile(std::vector<std::string> lines, std::stringstream &s)
  {
    size_t i = 0;
    std::string line;
    while (std::getline(s, line))
    {
      CHECK(line == lines.at(i));
      i++;
    }

    CHECK(i == lines.size());
    return true;
  }

  void BuildFileFromVector(std::vector<std::string> const &lines, std::stringstream &s)
  {
    for (auto line : lines)
    {
      s << line << "\n";
    }
  }
}
