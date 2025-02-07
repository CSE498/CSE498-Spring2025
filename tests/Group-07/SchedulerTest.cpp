#include <vector>
#include "../../Group-07/Team07Library/Scheduler.h"
#include "../../third-party/Catch/single_include/catch2/catch.hpp"


using namespace cse;

TEST_CASE("SchedulerTest", "Construct")
{
    Scheduler scheduler;
}

TEST_CASE("SchedulerTest", "Add")
{
    Scheduler scheduler;
    scheduler.AddProcess(0);
    CHECK(1== scheduler.GetCurrProcesses());
    CHECK(1==scheduler.GetTotalProcesses());
    CHECK(1== scheduler.GetUniqueProcesses());

    scheduler.AddProcess(1);
    CHECK(2== scheduler.GetCurrProcesses());
    CHECK(2== scheduler.GetTotalProcesses());
    CHECK(2== scheduler.GetUniqueProcesses());

    scheduler.AddProcess(1);
    CHECK(3== scheduler.GetCurrProcesses());
    CHECK(3== scheduler.GetTotalProcesses());
    CHECK(2== scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest", "Remove")
{
    Scheduler scheduler;

    scheduler.RemoveProcess(0);
    CHECK(0== scheduler.GetCurrProcesses());
    CHECK(0==scheduler.GetTotalProcesses());
    CHECK(0== scheduler.GetUniqueProcesses());

    scheduler.AddProcess(0);
    scheduler.AddProcess(0);
    scheduler.AddProcess(1);

    scheduler.RemoveProcess(0);
    CHECK(2== scheduler.GetCurrProcesses());
    CHECK(2== scheduler.GetTotalProcesses());
    CHECK(2== scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest", "Update")
{
    Scheduler scheduler;
    scheduler.UpdateProcessCount(1, 12);
    CHECK(12== scheduler.GetCurrProcesses());
    CHECK(12== scheduler.GetTotalProcesses());
    CHECK(1== scheduler.GetUniqueProcesses());

    scheduler.UpdateProcessCount(1, -1);
    CHECK(12== scheduler.GetCurrProcesses());
    CHECK(12== scheduler.GetTotalProcesses());
    CHECK(1== scheduler.GetUniqueProcesses());

    scheduler.AddProcess(0);
    scheduler.UpdateProcessCount(0, 12);
    CHECK(24== scheduler.GetCurrProcesses());
    CHECK(24== scheduler.GetTotalProcesses());
    CHECK(2== scheduler.GetUniqueProcesses());

    scheduler.UpdateProcessCount(1, 0);
    CHECK(12== scheduler.GetCurrProcesses());
    CHECK(12== scheduler.GetTotalProcesses());
    CHECK(1== scheduler.GetUniqueProcesses());
}

TEST_CASE("SchedulerTest", "Queue")
{
    Scheduler scheduler, scheduler2, scheduler3;
    CHECK(-1== scheduler.GetNextProcess());

    scheduler.AddProcess(1);
    CHECK(1== scheduler.GetNextProcess());
    CHECK(-1== scheduler.GetNextProcess());

    scheduler.AddProcess(2);
    scheduler.AddProcess(1);
    scheduler.AddProcess(3);
    std::vector<int> expected = {1, 2, 3}, actual = {};
    while (!scheduler.empty())
    {
        actual.push_back(scheduler.GetNextProcess());
    }
    CHECK(expected== actual);

    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < i; j++)
        {
            scheduler2.AddProcess(i);
        }
    }
    expected = {4, 4, 4, 4, 3, 3, 3, 2, 2, 1};
    actual = {};
    while (!scheduler2.empty())
    {
        actual.push_back(scheduler2.GetNextProcess());
    }
    CHECK(expected== actual);

    for (int i = 0; i < 10; i++)
    {
        scheduler3.AddProcess(1);
        scheduler3.GetNextProcess();
    }
    expected = {1, 4, 4};
    actual = {};
    scheduler3.AddProcess(4);
    scheduler3.AddProcess(1);
    scheduler3.AddProcess(4);
    while (!scheduler3.empty())
    {
        actual.push_back(scheduler3.GetNextProcess());
    }

    CHECK(expected== actual);
}