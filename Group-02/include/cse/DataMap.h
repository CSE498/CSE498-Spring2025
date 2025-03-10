/**
* @file DataMap.h
* @author Rahul Baragur
*/

#pragma once

#include <any>
#include <cassert>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <sstream>


namespace cse {

/**
* DataMap Class
* (implementation decision to utilize composition rather than inheritance as ActionMap class is made easier since
 * it uses DataMap)
 * Allows for std::string key and any value desired as key value pair held within class
*/
class DataMap {
 private:
  //constant for default value
  static constexpr int DEFAULT_VALUE = 0;

  /// Member Variable unordered_map
  std::unordered_map<std::string, std::any> m_map;

 public:
  /**
   * Default constructor
   */
  DataMap() = default;

  [[maybe_unused]] DataMap(std::initializer_list<std::pair<std::string, std::any>> initial);

  /**
   * Copy constructor
   * @param other DataMap to be copied
   */
  DataMap(const DataMap& other) = default;

  /**
   * Assignment operator
   * @param other DataMap to be copied
   * @return reference to DataMap
   */
  DataMap& operator=(const DataMap& other) = default;

  /**
  * Insert key value pair into DataMap
   *
   * (For grading purposes of initial specs, this function was renamed from set to insert to better match the standard
   * library)
  * @tparam T any value
  * @param name key name to be inserted
  * @param val value to be associated with key within DataMap
  */
  template <typename T>
  [[maybe_unused]] void insert(const std::string& name, const T& val) {
    // https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert custom messages in assert trick I have implemented within
    assert(!contains(name) && "Key already exists within DataMap");
    m_map[name] = val;
  }

  std::any& operator[](const std::string& key);

  /**
  * .at method for finding where key is
  * @tparam T templated value returned
  * @param name std::string
  * @return
  */
  template <typename T>
  [[maybe_unused]] T at(const std::string& name) {
    assert(contains(name) && "Key does not exist in DataMap");
    const std::any& val = m_map[name];
    assert(val.type() == typeid(T) && "Wrong type requested from what is contained within DataMap for value");
    return std::any_cast<T>(m_map[name]);
  }

  /**
   * Emulate behavior of the [] operator as in std::unordered map
   * Get value from key std::string
   * If key does not exist, set key to defaulted any templated value constructor
   * @tparam T templated value returned
   * @param name std::string
   * @return T
   */
  template <typename T>
  [[maybe_unused]] T get(const std::string& name) {
    if (!m_map.contains(name)) {
      m_map[name] = std::any(T());
    }
    assert(m_map[name].type() == typeid(T) && "Wrong type requested from what is contained within DataMap for value");
    return std::any_cast<T>(m_map[name]);
  }

  [[nodiscard]] bool contains(const std::string& name) const;

  /**
    * Delete a key from the map
    * @param name key to be deleted
    */
  [[maybe_unused]] void erase(const std::string& name) {
    assert(contains(name) && "Key does not exist in DataMap");
    m_map.erase(name);
  }

  /**
    * Clear the DataMap
    */
  [[maybe_unused]] void clear() {
    assert(!empty() && "Datamap is not empty");
    m_map.clear();
  }

  /**
    * Gives the size of the map
    * @return unsigned long map size
    */
  [[maybe_unused]] [[nodiscard]] size_t size() const {
    return m_map.size();
  }

  /**
    * Emptys the DataMap
    */
  [[maybe_unused]] [[nodiscard]] bool empty() const {
    return m_map.empty();
  }

  /**
    * Returns the count of the keys within the map
    * @param name key to be found
    * @return unsigned long # of keys
    */
  [[maybe_unused]] [[nodiscard]] size_t count(const std::string& name) const {
    return m_map.count(name);
  }

  /**
   * Converts a value into a string using a stringstream
   * @tparam T templated value
   * @param name key of associated value
   * @return std::string of value
   */
  template <typename T>
  [[maybe_unused]] std::string to_string(const std::string & name) {
    assert(contains(name) && "Key does not exist in DataMap");
    T value = get<T>(name);
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

};
}  // namespace cse