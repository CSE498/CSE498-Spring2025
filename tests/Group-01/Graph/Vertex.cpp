#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Graph/Vertex.hpp"
#include "../../../Group-01/Graph/Edge.hpp"
#include "../Utils/TestUtils.hpp"

#include <vector>
#include <sstream>

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse::Vertex", "[base]")
{
  cse::Vertex v("id1");

  REQUIRE_THAT(v.GetX(), WithinAbs(0, cse_test_utils::FLOAT_DELTA));
  REQUIRE_THAT(v.GetY(), WithinAbs(0, cse_test_utils::FLOAT_DELTA));
  CHECK(v.GetId() == "id1");

  std::ostringstream os;
  os << v;
  CHECK(os.str() == "Vertex(id1)");
}

TEST_CASE("Test cse::Vertex - Edges", "[base] - Edge")
{
  auto v1 = std::make_shared<cse::Vertex>("id1");
  auto v2 = std::make_shared<cse::Vertex>("id2");
  auto v3 = std::make_shared<cse::Vertex>("id3");

  // Single direction edge
  auto e1 = std::make_shared<cse::Edge>("edge1", v1, v2);
  v1->AddEdge(e1);
  CHECK(v1->IsConnected(*v2));
  CHECK(!v1->IsConnected(*v3));
}

TEST_CASE("Test cse::Vertex - To file", "Export to file")
{
  auto v1 = std::make_shared<cse::Vertex>("id1");
  std::stringstream s;
  v1->ToFile(s, 1);
  std::vector<std::string> lines{"  VERTEX:id1", "    X:0", "    Y:0"};
  REQUIRE(cse_test_utils::CheckForStringFile(lines, s));
}

TEST_CASE("Test cse::Vertex - From file", "Read from file")
{
  std::vector<std::string> lines{"  VERTEX:id1", "    X:1", "    Y:1"};
  std::stringstream s;
  cse_test_utils::BuildFileFromVector(lines, s);

  auto v1 = std::make_shared<cse::Vertex>(s, 2);
  REQUIRE_THAT(v1->GetX(), WithinAbs(1, cse_test_utils::FLOAT_DELTA));
  REQUIRE_THAT(v1->GetY(), WithinAbs(1, cse_test_utils::FLOAT_DELTA));
  CHECK(v1->GetId() == "id1");
}
