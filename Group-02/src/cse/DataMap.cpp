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
[[maybe_unused]] DataMap::DataMap(std::initializer_list<std::pair<std::string, std::any>> initial) {
  for (const auto& pair : initial) {
    m_map[pair.first] = pair.second;
  }
}

/**
* Check if key is within the DataMap
* @param name std::string name to be found
* @return bool if key exists or not
 *
 * (For grading purposes of initial specs, this function function was renamed from keyContains to better fit naming
 * convention)
*/
bool DataMap::contains(const std::string& name) const {
  return (m_map.find(name) != m_map.end());
}

/**
 * Operator overload for Datamap []
 * Defaults to 0 if called DataMap["key"]
 * Allows for assignment DataMap["key"] = 90
 * @param key
 * @return std::any&
 */
std::any& DataMap::operator[](const std::string& key) {
  if (!m_map.contains(key)) {
    m_map[key] = std::any(DEFAULT_VALUE);
  }
  return m_map[key];
}

}  // namespace cse