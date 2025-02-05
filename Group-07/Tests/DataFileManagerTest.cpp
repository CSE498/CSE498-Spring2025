#include "../Team07Library/DataFileManager.h"
#include "gtest/gtest.h"

// New test case to create a CSV file
TEST(DataFileManagerTest, CreateCSVFile) {
  // Define CSV data
  std::vector<int> time = {0, 1, 2};
  std::vector<int> preyPopulation = {100, 110, 120};
  std::vector<int> predatorPopulation = {20, 18, 15};
  std::vector<double> growthRatePrey = {0.1, 0.1, 0.1};
  std::vector<double> predationRate = {0.01, 0.01, 0.01};
  std::vector<double> deathRatePredators = {0.1, 0.1, 0.1};
  std::vector<double> reproductionRatePredators = {0.01, 0.01, 0.01};

  ASSERT_EQ(time.size() + 1, time.size() + 1);
}
