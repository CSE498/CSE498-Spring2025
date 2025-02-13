/**
* @file DataMap.cpp
* @author Rahul Baragur
*/

#include <cse/DataMap.h>

namespace cse {

/**
 * Constructor to allow initializer list for DataMap
 * @param initial std::initializer list of a pair of string and any
 */
DataMap::DataMap(std::initializer_list<std::pair<std::string, std::any>> initial) {
  for (const auto& keyvalue : initial) {
    m_map[keyvalue.first] = keyvalue.second;
  }
}

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

/**
 * Operator overload for Datamap []
 * defaults to 0 if called DataMap["key"]
 * Allows for assignment DataMap["key"] = 90
 * @param key
 * @return std::any&
 */
std::any& DataMap::operator[](const std::string& key) {
  if (!m_map.contains(key)) {
    m_map[key] = 0;
  }
  return m_map[key];
}

}  // namespace cse