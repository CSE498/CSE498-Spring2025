#include <vector>

#include "../../Group-07/Team07Library/Scheduler.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("SchedulerTest Construct", "[Scheduler]") {
  cse::Scheduler scheduler;

  CHECK(0 == scheduler.GetCurrProcesses());
  CHECK(0 == scheduler.GetTotalProcesses());
  CHECK(0 == scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest Add", "[Scheduler]") {
  cse::Scheduler scheduler;
  scheduler.AddProcess(0);
  CHECK(1 == scheduler.GetCurrProcesses());
  CHECK(1 == scheduler.GetTotalProcesses());
  CHECK(1 == scheduler.GetUniqueProcesses());

  scheduler.AddProcess(1);
  CHECK(2 == scheduler.GetCurrProcesses());
  CHECK(2 == scheduler.GetTotalProcesses());
  CHECK(2 == scheduler.GetUniqueProcesses());

  scheduler.AddProcess(1);
  CHECK(3 == scheduler.GetCurrProcesses());
  CHECK(3 == scheduler.GetTotalProcesses());
  CHECK(2 == scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest Remove", "[Scheduler]") {
  cse::Scheduler scheduler;

  scheduler.RemoveProcess(0);
  CHECK(0 == scheduler.GetCurrProcesses());
  CHECK(0 == scheduler.GetTotalProcesses());
  CHECK(0 == scheduler.GetUniqueProcesses());

  scheduler.AddProcess(0);
  scheduler.AddProcess(0);
  scheduler.AddProcess(1);

  scheduler.RemoveProcess(0);
  CHECK(2 == scheduler.GetCurrProcesses());
  CHECK(2 == scheduler.GetTotalProcesses());
  CHECK(2 == scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest Empty", "[Scheduler]") {
  cse::Scheduler scheduler;
  CHECK(true == scheduler.empty());

  scheduler.AddProcess(0);
  CHECK(false == scheduler.empty());

  scheduler.RemoveProcess(0);
  CHECK(true == scheduler.empty());
}

TEST_CASE("SchedulerTest Update", "[Scheduler]") {
  cse::Scheduler scheduler;
  scheduler.SetProcessCount(1, 12);
  CHECK(12 == scheduler.GetCurrProcesses());
  CHECK(12 == scheduler.GetTotalProcesses());
  CHECK(1 == scheduler.GetUniqueProcesses());

  scheduler.SetProcessCount(1, -1);
  CHECK(12 == scheduler.GetCurrProcesses());
  CHECK(12 == scheduler.GetTotalProcesses());
  CHECK(1 == scheduler.GetUniqueProcesses());

  scheduler.AddProcess(0);
  scheduler.SetProcessCount(0, 12);
  CHECK(24 == scheduler.GetCurrProcesses());
  CHECK(24 == scheduler.GetTotalProcesses());
  CHECK(2 == scheduler.GetUniqueProcesses());

  scheduler.SetProcessCount(1, 0);
  CHECK(12 == scheduler.GetCurrProcesses());
  CHECK(12 == scheduler.GetTotalProcesses());
  CHECK(1 == scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest Queue", "[Scheduler]") {
  cse::Scheduler scheduler, scheduler2, scheduler3;
  CHECK(std::nullopt == scheduler.PopNextProcess());

  scheduler.AddProcess(1);
  CHECK(1 == scheduler.PopNextProcess());
  CHECK(std::nullopt == scheduler.PopNextProcess());

  scheduler.AddProcess(2);
  scheduler.AddProcess(1);
  scheduler.AddProcess(3);
  std::vector<std::optional<int>> expected = {1, 2, 3}, actual = {};
  while (!scheduler.empty()) {
    actual.push_back(scheduler.PopNextProcess());
  }
  CHECK(expected == actual);

  for (int i = 1; i <= 4; i++) {
    for (int j = 0; j < i; j++) {
      scheduler2.AddProcess(i);
    }
  }
  expected = {4, 4, 4, 4, 3, 3, 3, 2, 2, 1};
  actual = {};
  while (!scheduler2.empty()) {
    actual.push_back(scheduler2.PopNextProcess());
  }
  CHECK(expected == actual);

  for (int i = 0; i < 10; i++) {
    scheduler3.AddProcess(1);
    scheduler3.PopNextProcess();
  }
  expected = {1, 4, 4};
  actual = {};
  scheduler3.AddProcess(4);
  scheduler3.AddProcess(1);
  scheduler3.AddProcess(4);
  while (!scheduler3.empty()) {
    actual.push_back(scheduler3.PopNextProcess());
  }

  CHECK(expected == actual);
}