#include "../../../Group-01/Random/Random.hpp"

#include <vector>

#include "../../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("Test cse::Random", "[base]") {
  cse::Random random(42);

  // Test integer ranges
  auto int_val = random.GetInt(1, 100);
  CHECK(int_val >= 1);
  CHECK(int_val <= 100);

  // Test negative ranges
  auto neg_val = random.GetInt(-10, 10);
  CHECK(neg_val >= -10);
  CHECK(neg_val <= 10);

  // Test double ranges
  auto double_val = random.GetDouble(0.0, 1.0);
  CHECK(double_val >= 0.0);
  CHECK(double_val <= 1.0);

  // Test larger double ranges
  auto large_val = random.GetDouble(-100.0, 100.0);
  CHECK(large_val >= -100.0);
  CHECK(large_val <= 100.0);

  // Test probability extremes
  CHECK(random.P(1.0));  
  CHECK(!random.P(0.0)); 
  
  // Test min == max edge case
  auto equal_int = random.GetInt(9, 9);
  CHECK(equal_int == 9);
  
  auto equal_double = random.GetDouble(2.22, 2.22);
  CHECK(equal_double == 2.22);
}

TEST_CASE("Test cse::Random - Seeds", "[base]") {
  // Test seed reproducibility
  cse::Random r1(42);
  cse::Random r2(42);

  // Same seeds should produce same values 
  {
    auto val1 = r1.GetInt(1, 100);
    auto val2 = r2.GetInt(1, 100);
    CHECK(val1 == val2);

    auto dval1 = r1.GetDouble(0.0, 1.0);
    auto dval2 = r2.GetDouble(0.0, 1.0);
    CHECK(dval1 == dval2);
  }

  // Different seeds should produce different values 
  {
    cse::Random r3(43);
    auto val1 = r1.GetInt(1, 100);
    auto val3 = r3.GetInt(1, 100);
    CHECK(val1 != val3);
  }

  // SetSeed should change the random sequence
  {
    r1.SetSeed(100);
    auto val1 = r1.GetInt(1, 100);
    auto val2 = r2.GetInt(1, 100);
    CHECK(val1 != val2);
  }
  
  // Test extreme seed values (created with assistance from ChatGPT)
  {
    cse::Random r_min(0);
    cse::Random r_max(UINT_MAX);
    
    // Verify they produce different sequences
    CHECK(r_min.GetInt(1, 1000) != r_max.GetInt(1, 1000));
  }
  
  // Test that setting the same seed twice produces the same sequence
  {
    r1.SetSeed(12345);
    auto first = r1.GetInt(1, 100);
    
    r1.SetSeed(12345);
    auto second = r1.GetInt(1, 100);
    
    CHECK(first == second);
  }
}

TEST_CASE("Test cse::Random - Distribution", "[base]") {
  cse::Random random(42);

  // Test dice example
  std::vector<int> counts(6, 0);
  for (int i = 0; i < 100; i++) {
    auto roll = random.GetInt(1, 6);
    counts[roll - 1]++;
  }

  // Each value should appear at least once 
  for (auto count : counts) {
    CHECK(count > 0);
  }
}

TEST_CASE("Test cse::Random - Template", "[base]") {
  cse::Random random(42);

  // Test template with different numeric types
  {
    auto val = random.Get<float>(0.0, 1.0);
    CHECK(val >= 0.0);
    CHECK(val <= 1.0);
  }

  {
    auto val = random.Get<double>(-1.0, 1.0);
    CHECK(val >= -1.0);
    CHECK(val <= 1.0);
  }

  {
    auto val = random.Get<int>(0, 100);
    CHECK(val >= 0);
    CHECK(val <= 100);
  }
}