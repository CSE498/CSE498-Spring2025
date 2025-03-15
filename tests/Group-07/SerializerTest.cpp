#include <climits>
#include <fstream>
#include <iostream>
#include <random>

#include "../../Group-07/Team07Library/Serializer.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

const int MAX_CASE = 100;
const int MAX_SIZE = 500;
const char filename[] = "result.bin";

std::random_device rd;
std::mt19937_64 gen(rd());

TEST_CASE("Serializer Construction", "[Serializer]")
{
  cse::Serializer Neutral;
  REQUIRE(Neutral.GetMode() == cse::Mode::SAVE);
  cse::Serializer Saver(cse::Mode::SAVE);
  REQUIRE(Saver.IsSave());
  cse::Serializer Loader(cse::Mode::LOAD);
  REQUIRE(Loader.IsLoad());
}

TEST_CASE("Serializer Destruction", "[Serialzer]")
{
  static bool called = false;
  class TestSerializer : public cse::Serializer
  {
  public:
    ~TestSerializer() { called = true; }
  };
  called = false;
  {
    TestSerializer test;
  }
  REQUIRE(called);
}

TEST_CASE("Serializer Swap Mode", "[Serializer]")
{
  cse::Serializer Neutral;
  REQUIRE(Neutral.IsSave());
  Neutral.SetMode(cse::Mode::LOAD);
  REQUIRE(Neutral.IsLoad());
}

TEST_CASE("Serializer Save Load Basic", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  int number = 22;
  int result = -1;
  Saver.Serialize(number, filename);
  REQUIRE(result == -1);
  Loader.Serialize(result, filename);
  REQUIRE(result == number);
  std::remove(filename);
}

TEST_CASE("Serializer Save Load Fundamental Types", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  // Testing Int
  std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
  int Integer;
  for (int i = 0; i < MAX_CASE; i++)
  {
    Integer = ranInt(gen);
    int Result;
    Saver.Serialize(Integer, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(Integer == Result);
    std::remove(filename);
  }
  // Testing Char
  std::uniform_int_distribution<int> ranChar(static_cast<int>('A'),
                                             static_cast<int>('Z'));
  char Character;
  for (int i = 0; i < MAX_CASE; i++)
  {
    Character = static_cast<char>(ranChar(gen));
    char Result;
    Saver.Serialize(Character, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(Character == Result);
    std::remove(filename);
  }
  // Testing Long Long
  std::uniform_int_distribution<long long> ranLL(LLONG_MIN, LLONG_MAX);
  long long LL;
  for (int i = 0; i < MAX_CASE; i++)
  {
    LL = ranLL(gen);
    long long Result;
    Saver.Serialize(LL, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(LL == Result);
    std::remove(filename);
  }
  // Testing Double
  std::uniform_real_distribution<double> ranDBL(-MAX_SIZE, MAX_SIZE);
  double Double;
  for (int i = 0; i < MAX_CASE; i++)
  {
    Double = ranDBL(gen);
    double Result;
    Saver.Serialize(Double, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(Double == Result);
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load String", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranChar(static_cast<int>(' '),
                                               static_cast<int>('~'));
    int Length = ranInt(gen);
    std::string String = "";
    for (int l = 0; l < Length; l++)
    {
      char Character = static_cast<char>(ranChar(gen));
      String = String + Character;
    }
    std::string Result;
    Saver.Serialize(String, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(String == Result);
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Vector", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    int Length = ranSize(gen);
    std::vector<int> vec;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      vec.push_back(value);
    }
    std::vector<int> Result;
    Saver.Serialize(vec, filename);
    Loader.Serialize(Result, filename);
    for (int l = 0; l < Length; l++)
    {
      REQUIRE(vec[l] == Result[l]);
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Array", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  const int size = MAX_SIZE;
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    std::array<int, size> arr;
    for (int l = 0; l < size; l++)
    {
      int value = ranInt(gen);
      arr[l] = value;
    }
    std::array<int, size> Result;
    Saver.Serialize(arr, filename);
    Loader.Serialize(Result, filename);
    REQUIRE(Result.size() == size);
    for (int l = 0; l < size; l++)
    {
      REQUIRE(arr[l] == Result[l]);
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Set", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    int Length = ranSize(gen);
    std::set<int> s, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      s.insert(value);
    }
    Saver.Serialize(s, filename);
    Loader.Serialize(res, filename);
    REQUIRE(res.size() == s.size());
    auto is = s.begin();
    auto ir = res.begin();
    for (int l = 0; l < Length; l++)
    {
      REQUIRE(*is == *ir);
      is++, ir++;
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Unordered Set", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    int Length = ranSize(gen);
    std::unordered_set<int> s, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      s.insert(value);
    }
    Saver.Serialize(s, filename);
    Loader.Serialize(res, filename);
    REQUIRE(res.size() == s.size());
    int len = static_cast<int>(s.size());
    auto is = s.begin();
    auto ir = res.begin();
    for (int l = 0; l < len; l++)
    {
      REQUIRE((res.find(*is) != res.end() && s.find(*ir) != s.end()));
      is++, ir++;
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Multiset", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    int Length = ranSize(gen);
    std::multiset<int> s, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      s.insert(value);
    }
    Saver.Serialize(s, filename);
    Loader.Serialize(res, filename);
    REQUIRE(res.size() == s.size());
    auto is = s.begin();
    auto ir = res.begin();
    for (int l = 0; l < Length; l++)
    {
      REQUIRE(*is == *ir);
      is++, ir++;
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Unordered Multiset", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    int Length = ranSize(gen);
    std::unordered_multiset<int> s, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      s.insert(value);
    }
    Saver.Serialize(s, filename);
    Loader.Serialize(res, filename);
    REQUIRE(res.size() == s.size());
    std::unordered_map<int, int> cs, cr;
    for (const auto &v : s)
      cs[v]++;
    for (const auto &v : res)
      cr[v]++;
    REQUIRE(cs == cr);
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Map", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::map<int, int> m, res;
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      int value = ranInt(gen);
      m[l] = value;
    }
    Saver.Serialize(m, filename);
    Loader.Serialize(res, filename);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      REQUIRE(res.find(l) != res.end());
      REQUIRE(res[l] == m[l]);
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Unordered Map", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::unordered_map<int, int> m, res;
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      int value = ranInt(gen);
      m[l] = value;
    }
    Saver.Serialize(m, filename);
    Loader.Serialize(res, filename);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      REQUIRE(res.find(l) != res.end());
      REQUIRE(res[l] == m[l]);
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Multi Map", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::multimap<int, int> m, res;
    std::uniform_int_distribution<int> ranKey(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      int key = ranKey(gen);
      int value = ranInt(gen);
      m.insert({key, value});
    }
    Saver.Serialize(m, filename);
    Loader.Serialize(res, filename);
    REQUIRE(m == res);
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Unordered Multi Map", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::unordered_multimap<int, int> m, res;
    std::uniform_int_distribution<int> ranKey(INT_MIN, INT_MAX);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    for (int l = 0; l < MAX_SIZE; l++)
    {
      int key = ranKey(gen);
      int value = ranInt(gen);
      m.insert({key, value});
    }
    Saver.Serialize(m, filename);
    Loader.Serialize(res, filename);
    REQUIRE(m == res);
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Stack", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    int Length = ranSize(gen);
    std::stack<int> s, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      s.push(value);
    }
    Saver.Serialize(s, filename);
    Loader.Serialize(res, filename);
    REQUIRE(s.size() == res.size());
    while (!s.empty())
    {
      REQUIRE(s.top() == res.top());
      s.pop();
      res.pop();
    }
    std::remove(filename);
  }
  std::remove(filename);
}

TEST_CASE("Serializer Save Load Queue", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    int Length = ranSize(gen);
    std::queue<int> q, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      q.push(value);
    }
    Saver.Serialize(q, filename);
    Loader.Serialize(res, filename);
    REQUIRE(q.size() == res.size());
    while (!q.empty())
    {
      REQUIRE(q.front() == res.front());
      q.pop();
      res.pop();
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Priority Queue", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    int Length = ranSize(gen);
    std::priority_queue<int> pq, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      pq.push(value);
    }
    Saver.Serialize(pq, filename);
    Loader.Serialize(res, filename);
    REQUIRE(pq.size() == res.size());
    while (!pq.empty())
    {
      REQUIRE(pq.top() == res.top());
      pq.pop();
      res.pop();
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Save Load Deque", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  for (int i = 0; i < MAX_CASE; i++)
  {
    std::uniform_int_distribution<int> ranSize(1, MAX_SIZE);
    std::uniform_int_distribution<int> ranInt(INT_MIN, INT_MAX);
    int Length = ranSize(gen);
    std::deque<int> d, res;
    for (int l = 0; l < Length; l++)
    {
      int value = ranInt(gen);
      d.push_back(value);
    }
    Saver.Serialize(d, filename);
    Loader.Serialize(res, filename);
    REQUIRE(d.size() == res.size());
    for (size_t i = 0; i < d.size(); i++)
    {
      REQUIRE(d[i] == res[i]);
    }
    std::remove(filename);
  }
}

TEST_CASE("Serializer Empty File or Empty Containers", "[Serializer]")
{
  cse::Serializer Saver(cse::Mode::SAVE);
  cse::Serializer Loader(cse::Mode::LOAD);
  std::remove(filename);
  std::vector<int> vec, res; // Keep vec empty
  Saver.Serialize(vec, filename);
  Loader.Serialize(res, filename);
  REQUIRE(res.size() == 0);
  std::remove(filename);
  Loader.Serialize(res, filename); // It must raise error
}