#pragma once

#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <type_traits>

using std::invalid_argument;
using std::is_arithmetic;
using std::is_floating_point;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

namespace cse {
class Random {
 private:
  mt19937 generator;

 public:
  Random(unsigned int seed);
  double GetDouble(double min, double max);
  int GetInt(int min, int max);
  bool P(double probability);
  void SetSeed(unsigned int seed);

  template <typename T>
  T Get(T min, T max) {
    static_assert(is_arithmetic<T>::value, "not a numeric type");
    assert(max >= min);

    if constexpr (is_floating_point<T>::value) {
      uniform_real_distribution<T> dist(min, max);
      return dist(generator);
    } else {
      uniform_int_distribution<T> dist(min, max);
      return dist(generator);
    }
  }
};

Random::Random(unsigned int seed) : generator(seed) {}

double Random::GetDouble(double min, double max) {
  assert(max >= min);
  uniform_real_distribution<double> distribution(min, max);
  return distribution(generator);
}

int Random::GetInt(int min, int max) {
  assert(max >= min);
  uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

bool Random::P(double probability) {
  assert(probability >= 0.0);
  assert(probability <= 1.0);
  uniform_real_distribution<double> distribution(0.0, 1.0);
  return distribution(generator) < probability;
}

void Random::SetSeed(unsigned int seed) { generator.seed(seed); }

}  // namespace cse