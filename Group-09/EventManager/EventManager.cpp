/**
 * @file EventManager.cpp
 * @author Grace Fitzgerald
 */

#include "EventManager.hpp"


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
  while ((event_queue_.size() > 0) && !paused_events_.count(event_queue_.peek().getID())
      && event_queue_.peek().getTime() <= clock_time_) {
    std::cout << event_queue_.peek().getData() << "\n"; //Placeholder for handling events
    running_events_.erase(event_queue_.peek().getID());
    event_queue_.pop();
  }
  if (event_queue_.size() == 0) {
    running_ = false;
  }
}

/**
 * @brief Adds event_id to paused_events set
 * @param event_id The event to be paused
 * @return true if successful, false if event does not exist in queue
 */
bool EventManager::PauseEvent(int event_id) {
  assert( ((paused_events_.count(event_id) > 0) ||
    (running_events_.count(event_id) > 0)) && "Event ID must be a managed ID."  );
  if (paused_events_.count(event_id) > 0) {
    return true;
  } else if (running_events_.count(event_id) > 0) {
    paused_events_.insert(event_id);
    running_events_.erase(event_id);
    return true;
  }
  return false;
}

/**
 * @brief Removes event to paused_events set
 * @param event_id The event to be resumedd
 * @return true if successfully removed, false if event is not currently paused
 */
bool EventManager::ResumeEvent(int event_id) {
  assert( ((paused_events_.count(event_id) > 0) ||
      (running_events_.count(event_id) > 0)) && "Event ID must be a managed ID."  );
  if (running_events_.count(event_id) > 0) {
    return true;
  } else if (paused_events_.count(event_id) > 0) {
    paused_events_.erase(event_id);
    running_events_.insert(event_id);
    return true;
  }
  return false;
}

/**
 * @brief Adds event to event_queue
 * @param event The event to be added
 * @return true if successful, false if unsuccessful
 */
bool EventManager::AddEvent(Event &event) {
  if (paused_events_.count(event.getID()) > 0 || running_events_.count(event.getID()) > 0)
    return false; // Event id is already in queue
  event_queue_.add(event);
  running_events_.insert(event.getID());
  return true;
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
  if (running_) { //Queue is already running
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