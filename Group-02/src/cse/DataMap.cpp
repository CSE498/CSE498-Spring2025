/**
* @file DataMap.cpp
* @author Rahul Baragur
*/

#include <cse/DataMap.h>

namespace cse {

/**
* Check if key is within the DataMap
* @param name std::string name to be found
* @return bool if key exists or not
*/
bool DataMap::contains(const std::string& name) {
  if (m_map.find(name) == m_map.end()) {
    return false;
  }
  return true;
}

}  // namespace cse