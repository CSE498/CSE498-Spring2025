/**
 * @file Event.h
 *
 * @author Owen Haiar
 */

#pragma once

namespace cse {

/**
 * @brief A struct to represent an event
 */
struct Event {
 private:
  int id;
  int time;
  std::string data;
 public:
  Event(int id, int time, std::string data) : id(id), time(time), data(std::move(data)) {}
  [[nodiscard]] inline int getID() const { return id; }
  [[nodiscard]] inline int getTime() const { return time; }
  [[nodiscard]] inline std::string getData() const { return data; }
  inline bool operator==(const Event &other) const { return id == other.id; }
  inline bool operator!=(const Event &other) const { return id != other.id; }
};

} // namespace cse

