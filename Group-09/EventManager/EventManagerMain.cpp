/**
 * @file EventManagerMain.cpp
 * @author Grace Fitzgerald
 */

#include <iostream>
#include "EventManager.hpp"
using namespace cse;

int main(){
  ///Simple EventManager demonstration
  cse::EventManager event_manager;
  std::string str  = "Printing some event";
  std::string str1 = "Another print statement";
  std::string str2 = "Another one";
  std::string str3 = "Duplicate";
  cse::Event event(1,5, str1);
  cse::Event event1(2,7, str2);
  cse::Event event2(3,3, str);
  cse::Event event3(4,7, str3);
  event_manager.AddEvent(event);
  event_manager.AddEvent(event1);
  event_manager.AddEvent(event3);
  event_manager.AddEvent(event2);
  event_manager.StartQueue();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  cse::Event event4(5,9, str2);
  event_manager.AddEvent(event4);
  cse::Event event5(6,11, str2);
  event_manager.AddEvent(event5);
  event_manager.PauseEvent(event5.getID());
  std::this_thread::sleep_for(std::chrono::seconds(10));
  return 0;
}