/**
 * @file EventQueue.h
 *
 * @author Owen Haiar
 */

#pragma once

#include <optional>
#include <queue>
#include <unordered_set>
#include "../Event/Event.hpp"

namespace cse {

/**
 * @brief Compares two events by time for use in priority queue
 */
struct EventCompare {
  bool operator()(const Event &a, const Event &b) {
	return a.getTime() > b.getTime();
  }
};

class EventQueue {
 public:
  EventQueue() = default;
  ~EventQueue() = default;
  void add(const Event &);
  std::optional<Event> remove(const Event &);
  Event pop();
  Event peek();
  void update(const Event &);
  void print();
  [[nodiscard]] inline size_t size() const { return eventCount; }
 private:
  std::priority_queue<Event, std::vector<Event>, EventCompare> heap;
  std::unordered_set<int> ids;
  size_t eventCount = 0;
};

}

