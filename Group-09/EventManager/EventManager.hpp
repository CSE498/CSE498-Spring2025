/**
 * @file EventManager.hpp
 * @author Grace Fitzgerald
 *
 *
 */

#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <utility>
#include <set>
#include <cassert>
#include "../Event/Event.hpp"
#include "../EventQueue/EventQueue.hpp"

namespace cse {

class EventManager {
 private:
  EventQueue event_queue_;
  int clock_time_ = 0; //Temporary to keep track of time
  std::atomic<bool> running_{false};
  std::thread clock_thread_;
  std::set<int> paused_events_;
  std::set<int> running_events_;
  void AdvanceTime();
  void TriggerEvents();

 public:
  EventManager() = default;
  ~EventManager() { StopQueue(); };
  bool PauseEvent(int event_id);
  bool ResumeEvent(int event_id);
  bool AddEvent(cse::Event &event);
  void StopQueue();
  void StartQueue();
  void RestartQueue();
  /**
   * @brief Get the number of paused events
   * @return The number of paused events
   */
  size_t getNumPaused() const { return paused_events_.size(); }

  /**
   * @brief Get the number of events being managed
   * @return The number of events in event_queue_ as size_t
   */
  size_t getNumEvents() const { return (paused_events_.size() + running_events_.size()); }

  /**
   * @brief Get the current internal time
   * @return The current time in seconds
   */
  int getTime() const { return clock_time_; }

};

}

