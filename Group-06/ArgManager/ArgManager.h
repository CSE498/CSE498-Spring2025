/**
 * @file ArgManager.cpp
 * @author By Will Crawford
 * @brief The Arg Manger Class
 */

#ifndef ARGMANAGER__ARGMANAGER_H
#define ARGMANAGER__ARGMANAGER_H
 
#include <functional>
#include <iostream>
#include <vector>
#include <string>
 
namespace cse {
 
/**
 * @brief the ArgManager class
 */
class ArgManager {
 public:
  ArgManager(int argc, char *argv[]);
  bool HasArg(const std::string& arg) const;
  std::string GetSingleOption(const std::string& arg) const;
  std::vector<std::string> GetListOfOptions(const std::string& arg) const;
  void PrintHelp();

 private:
  // store args

  /// @brief number of arguments
  int mArgc = 0;

  /// @brief List of options that have been given
  std::vector<std::string> mArgv;
};
}  // namespace cse

#endif  // ARGMANAGER__ARGMANAGER_H