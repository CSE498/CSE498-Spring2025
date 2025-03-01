/**
 * @file EventManager.cpp
 * @author Grace Fitzgerald
 */

#include "EventManager.hpp"
#include <optional>

namespace cse {

/**
 * @brief Increments time on clock_thread and checks for events to trigger
 */
void EventManager::AdvanceTime() {
  while (running_) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    clock_time_++;
    TriggerEvents();
  }
}

/**
 * @brief Checks for and triggers events
 */
void EventManager::TriggerEvents() {
  while (event_queue_.size() && event_queue_.peek().getTime() <= clock_time_) { //Events to be popped
    cse::Event e = event_queue_.peek();
    if (paused_events_.find(e.getID()) != paused_events_.end()) {
      event_queue_.pop(); //Skip over paused events
      continue;
    }
    std::cout << event_queue_.peek().getData() << "\n"; //Placeholder for handling events
    if (repeat_events_.find(e.getID()) != repeat_events_.end()) {
      cse::Event event(e.getID(), e.getTime() + repeat_events_[e.getID()], e.getData()); //Readd repeats to the queue
      event_queue_.update(event);
    } else {
      running_events_.erase(e.getID());
      event_queue_.pop();
    }
  }
  if (event_queue_.size() == 0) {
    running_ = false;
  }
}

/**
 * @brief Adds event to paused_events
 * @param event The event to be paused
 * @return true if successful, false if event does not exist in queue
 */
bool EventManager::PauseEvent(const Event &event) {
  int id = event.getID();
  assert(((paused_events_.find(id) != paused_events_.end()) ||
      (running_events_.count(id) > 0)) && "Event ID must be a managed ID.");
  if (paused_events_.count(id) > 0) {
    return true;
  } else if (running_events_.count(id)) {
    paused_events_.insert({id, event});
    running_events_.erase(id);
    return true;
  }
  return false;
}

/**
 * @brief Removes event to paused_events set
 * @param event The event to be resumed
 * @return true if successfully removed, false if event is not currently paused
 */
bool EventManager::ResumeEvent(const Event &event) {
  int eventId = event.getID();
  assert(((paused_events_.find(eventId) != paused_events_.end()) ||
      running_events_.count(eventId)) && "Event ID must be a managed ID.");
  if (running_events_.count(eventId)) {
    return true;
  } else if (paused_events_.find(eventId) != paused_events_.end()) {
    event_queue_.add(paused_events_.at(eventId));
    paused_events_.erase(eventId);
    running_events_.insert(eventId);
    return true;
  }
  return false;
}

/**
 * @brief Adds event to event_queue
 * @param event The event to be added
 * @return added Event
 */
std::optional<Event> EventManager::AddEvent(int time, std::string data) {
  assert(time > -1);
  Event event(next_id_, time, data);
  ++next_id_;
  event_queue_.add(event);
  running_events_.insert(event.getID());
  return event;
}

/**
 * @brief Adds event to repeat_events_
 * @param event The event to be repeated
 * @return true if successfully added to repeat_events, false if unsuccessful
 */
bool EventManager::RepeatEvent(const cse::Event &event, int time_interval) {
  assert(time_interval > 0);
  if (repeat_events_.count(event.getID())){
    repeat_events_.at(event.getID()) = time_interval;
    return true;
  }
  if (time_interval > 0 && (paused_events_.count(event.getID()) + running_events_.count(event.getID()))) {
    repeat_events_.insert({event.getID(), time_interval});
    return true;
  }
  return false;
}

/**
 * @brief Stops clock from running and triggering events
 */
void EventManager::StopQueue() {
  running_ = false;
  if (clock_thread_.joinable()) {
    clock_thread_.join();
  }
}

/**
 * @brief Starts clock and begins checking for events to trigger
 */
void EventManager::StartQueue() {
  if (running_ || clock_thread_.joinable()) {
    return;
  }
  clock_time_ = 0;
  running_ = true;
  clock_thread_ = std::thread(&EventManager::AdvanceTime, this); //Create thread that executes AdvanceTime
}

/**
 * @brief Restarts clock
 */
void EventManager::RestartQueue() {
  StopQueue();
  clock_time_ = 0;
  StartQueue();
}

}