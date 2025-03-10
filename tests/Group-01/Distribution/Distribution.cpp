#include "../../../Group-01/Distribution/Distribution.hpp"
#include "../../../third-party/Catch/single_include/catch2/catch.hpp"

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse::Distribution", "[base]") {
  cse::Distribution distribution;

  // Declaring my tolerances and my solved probabilities
  const double tolerance = 0.001;
  const double bin3 = 0.0081;
  const double bin3Cumulative = 0.99954;
  const double uni3 = 0.2;
  const double uni3Cumulative = 0.6;
  const double noChance = 0.0;
  const double probZero = 0.59049;

  // Test making a uniform distribution
  distribution.BuildUniform(5);
  CHECK_THAT(distribution.GetProb(3), Catch::Matchers::WithinAbs(uni3, tolerance));
  CHECK_THAT(distribution.GetCumulativeProb(3), Catch::Matchers::WithinAbs(uni3Cumulative, tolerance));
  CHECK_THAT(distribution.GetCumulativeProb(7), Catch::Matchers::WithinAbs(noChance, tolerance));

  // Test making a binomial distribution
  distribution.BuildBinomial(5, .1);
  CHECK_THAT(distribution.GetProb(3), Catch::Matchers::WithinAbs(bin3, tolerance));
  CHECK_THAT(distribution.GetCumulativeProb(3), Catch::Matchers::WithinAbs(bin3Cumulative, tolerance));
  CHECK_THAT(distribution.GetProb(0), Catch::Matchers::WithinAbs(probZero, tolerance));
  CHECK_THAT(distribution.GetCumulativeProb(0), Catch::Matchers::WithinAbs(probZero, tolerance));
  CHECK_THAT(distribution.GetCumulativeProb(7), Catch::Matchers::WithinAbs(noChance, tolerance));

  // Test distributions to see if you can use nonsence vals
  CHECK_THROWS_AS(distribution.BuildUniform(0), std::runtime_error);
  CHECK_THROWS_AS(distribution.BuildBinomial(-7, 1), std::runtime_error);
  CHECK_THROWS_AS(distribution.BuildBinomial(4, 5), std::out_of_range);
}