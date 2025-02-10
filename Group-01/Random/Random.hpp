#pragma once

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
    if (max < min) {
      throw invalid_argument("max cannot be less than min");
    }

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
  if (max < min) {
    throw invalid_argument("max cannot be less than min");
  }
  uniform_real_distribution<double> distribution(min, max);
  return distribution(generator);
}

int Random::GetInt(int min, int max) {
  if (max < min) {
    throw invalid_argument("max cannot be less than min");
  }
  uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

bool Random::P(double probability) {
  if (probability < 0.0 || probability > 1.0) {
    throw invalid_argument("probability isnt between 0.0 and 1.0");
  }
  uniform_real_distribution<double> distribution(0.0, 1.0);
  return distribution(generator) < probability;
}

void Random::SetSeed(unsigned int seed) { generator.seed(seed); }