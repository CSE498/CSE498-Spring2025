#include "CSVfile.h"
// #include "DataGrid.h"
// #include "Datum.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <tuple>

// namespace cse {

// DataGrid CSVfile::LoadCSV(const std::string &filename, char delimiter) {
//     std::ifstream file(filename);
//     if (!file)
//         throw std::runtime_error("Cannot open file: " + filename);
    
//     DataGrid grid;
//     std::string line;
//     while (std::getline(file, line)) {
//         std::istringstream lineStream(line);
//         std::string token;
//         std::vector<Datum> row;
//         while (std::getline(lineStream, token, delimiter)) {
//             // For this basic version, always store as a string.
//             row.push_back(Datum(token));
//         }
//         grid.AppendRow(row);  // Assumes DataGrid has an AppendRow method
//     }
//     return grid;
// }

// bool CSVfile::ExportCSV(const std::string &filename, const DataGrid &grid) {
//     std::ofstream outFile(filename);
//     if (!outFile)
//         throw std::runtime_error("Cannot write to file: " + filename);
    
//     auto [rows, cols] = grid.Shape();  // Assumes Shape() returns a tuple<int, int>
//     for (int i = 0; i < rows; ++i) {
//         auto row = grid.GetRow(i);  // Assumes GetRow returns a vector of Datum
//         for (int j = 0; j < cols; ++j) {
//             outFile << row[j].AsString(); // Assumes AsString returns a string representation
//             if (j < cols - 1)
//                 outFile << delimiter;
//         }
//         outFile << "\n";
//     }
//     return true;
// }

// }
