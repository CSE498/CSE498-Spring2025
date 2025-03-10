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
#include <map>
#include "../Event/Event.hpp"
#include "../EventQueue/EventQueue.hpp"

namespace cse {

class EventManager {
 private:
  EventQueue event_queue_;
  int clock_time_;
  int next_id_;
  std::atomic<bool> running_;
  std::thread clock_thread_;
  std::set<int> running_events_;
  std::unordered_map<int, Event> paused_events_;
  std::unordered_map<int, int> repeat_events_;
  void AdvanceTime();
  void TriggerEvents();

 public:
  EventManager() : clock_time_(0), next_id_(0), running_(false) {};
  ~EventManager() { StopQueue(); };
  bool PauseEvent(Event &event);
  bool ResumeEvent(Event &event_id);
  std::optional<Event> AddEvent(int time, std::string data);
  bool RepeatEvent(cse::Event &event, int time_interval);
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

