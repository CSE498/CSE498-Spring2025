/**
 * @file EventQueue.cpp
 *
 * @author Owen Haiar
 *
 */

#include "EventQueue.hpp"

#include <iostream>
#include <format>
#include <cassert>

namespace cse {

/**
 * @brief Adds an event to the EventQueue
 * @param e The event to add
 */
void EventQueue::add(const Event &e) {
  if (!ids.contains(e.getID())) {
	heap.push(e);
	ids.insert(e.getID());
	eventCount++;
  } else {
	auto msg = std::format("Error adding event: Event ID {} already exists in EventQueue", e.getID());
	throw std::invalid_argument(msg);
  }
}

/**
 * @brief Removes an event from the EventQueue
 * @param e The event to remove
 * @return The removed event, if it was found
 */
std::optional<Event> EventQueue::remove(const Event &e) {
  std::priority_queue<Event, std::vector<Event>, EventCompare> temp;
  std::optional<Event> removed;

  // Move all elements except the one to be removed to temp
  while (!heap.empty()) {
	if (heap.top() != e) temp.push(heap.top());
	else {
	  removed = heap.top();
	  ids.erase(e.getID());
	  eventCount--;
	}
	heap.pop();
  }

  // Reassign
  heap = std::move(temp);

  assert(!removed.has_value() || removed.value().getID() == e.getID());
  return removed;
}

/**
 * @brief Pops the event at the top of the EventQueue
 * @return The event at the top of the EventQueue
 */
Event EventQueue::pop() {
  assert(eventCount > 0); // Ensure there is an event to pop (heap is not empty)
  auto e = heap.top();
  heap.pop();
  eventCount--;
  ids.erase(e.getID());
  return e;
}

/**
 * @brief Returns the event at the top of the EventQueue, without removing
 * @return The event at the top of the EventQueue
 */
Event EventQueue::peek() {
  assert(eventCount > 0); // Ensure there is an event to pop (heap is not empty)
  return heap.top();
}

/**
 * @brief Updates an event in the EventQueue
 * @details The updated event must have the same ID as the event currently in the queue
 * @param e The event to update
 * @throws std::invalid_argument If an event with a matching ID is not found
 */
void EventQueue::update(const Event &e) {
  auto removed = this->remove(e);
  if (removed.has_value()) {
	assert(removed.value().getID() == e.getID()); // Reinsert same ID with updated time
	this->add(e);
  } else {
	auto msg = std::format("Error updating event: Event ID {} not found in EventQueue", e.getID());
	throw std::invalid_argument(msg);
  }
}

/**
 * @brief Prints the contents of the EventQueue to stdout
 */
void EventQueue::print() {
  std::priority_queue<Event, std::vector<Event>, EventCompare> temp = heap;

  for (size_t i = 0; !temp.empty(); i++) {
	auto e = temp.top();
	std::cout << "#" << i << ":"
			  << " ID: " << e.getID()
			  << " Time: " << e.getTime()
			  << " Data: " << e.getData()
			  << std::endl;
	temp.pop();
  }
}

} // namespace cse

