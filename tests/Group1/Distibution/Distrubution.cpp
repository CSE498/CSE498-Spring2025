#include "../../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../../Group-01/Distribution/Distribution.hpp"

using Catch::Matchers::WithinAbs;

TEST_CASE("Test cse498::Distribution", "[base]")\
{
  cse498::Distribution distribution;

  const double tolerance = 0.0001;
  const double bin3 = 0.0081;
  const double bin3cumulative = 0.99954;
  const double uni3 = 0.02;
  const double uni3cumulative = 0.6;


  // Test trying an empty distributiongi
  CHECK_THROWS_AS(distribution.getProb(2),std::runtime_error);
  CHECK_THROWS_AS(distribution.getCumulativeProb(0),std::runtime_error);
  
  // Test making a uniform distribution
  distribution.BuildUniform(5);
  CHECK(distribution.getProb(3) == uni3);
  CHECK(distribution.getCumulativeProb(3) == uni3cumulative);

  // Test making a binomial distribution
  distribution.BuildBinomial(5, .1);
  CHECK_THAT(distribution.getProb(3), Catch::Matchers::WithinAbs(bin3, tolerance));
  CHECK_THAT(distribution.getCumulativeProb(3), Catch::Matchers::WithinAbs(bin3cumulative, tolerance));

  // Test distributions to see if you can use nonsence vals
  CHECK_THROWS_AS(distribution.BuildUniform(0),std::runtime_error);
  CHECK_THROWS_AS(distribution.BuildBinomial(-7, 1),std::runtime_error);
  CHECK_THROWS_AS(distribution.BuildBinomial(4, 5),std::out_of_range);

  // Tests trials out of range
  distribution.BuildUniform(5);
  CHECK_THROWS_AS(distribution.getProb(-1),std::out_of_range);
  CHECK_THROWS_AS(distribution.getCumulativeProb(7),std::out_of_range);

  distribution.BuildBinomial(5, .1);
  CHECK_THROWS_AS(distribution.getProb(-1),std::out_of_range);
  CHECK_THROWS_AS(distribution.getCumulativeProb(7),std::out_of_range);

}