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

  // Open a file in write mode
  std::ofstream outFile("simulation_data.csv");

  // Check if the file is open
  ASSERT_TRUE(outFile.is_open());

  // Write the headers
  outFile << "Time,preyPopulation,predatorPopulation,growthRatePrey,PredationRate,deathRatePredators,reproductionRatePredators\n";

  // Write the data
  for (size_t i = 0; i < time.size(); ++i) {
    outFile << time[i] << "," << preyPopulation[i] << "," << predatorPopulation[i] << "," 
            << growthRatePrey[i] << "," << predationRate[i] << "," 
            << deathRatePredators[i] << "," << reproductionRatePredators[i] << "\n";
  }

  // Close the file
  outFile.close();
  
  // Verify that the file has been created and written to
  std::ifstream inFile("simulation_data.csv");
  ASSERT_TRUE(inFile.is_open());
  std::string line;
  size_t lineCount = 0;
  while (std::getline(inFile, line)) {
    ++lineCount;
  }
  inFile.close();

  ASSERT_EQ(lineCount, time.size() + 1);  // Including header
