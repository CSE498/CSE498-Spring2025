/**
 * @file Scheduler.h
 * @author Nathan Staniszewski
 *
 *
 */

#ifndef PROJECT_CSE498_SPRING2025_GROUP_07_TEAM07LIBRARY_SCHEDULER_H
#define PROJECT_CSE498_SPRING2025_GROUP_07_TEAM07LIBRARY_SCHEDULER_H

#include <map>
#include <vector>
#include <algorithm>

namespace cse
{
    class Scheduler
    {
    private:

        std::map<int, int> scheduleMap;
        std::map<int, double> timesCalled;
        std::vector<int> currIds;
        int currProcesses = 0;
        double totalProcesses = 0;
        bool needUpdate = true;

    public:
        Scheduler() = default;
        ~Scheduler() = default;

        void AddProcess(int id)
        {
            scheduleMap[id]++;
            timesCalled[id]++;
            if(scheduleMap[id]==1)
            {
                currIds.push_back(id);
            }
            totalProcesses++;
            currProcesses++;
            needUpdate=true;
        }
        void RemoveProcess(int id)
        {
            if(scheduleMap.find(id)!=scheduleMap.end() && scheduleMap[id]>0)
            {
                scheduleMap[id]--;
                timesCalled[id]--;
                totalProcesses--;
                currProcesses--;
                if(scheduleMap[id]==0)
                {
                    currIds.erase(std::find(currIds.begin(),currIds.end(),id));
                }
            }
            needUpdate=true;
        }
        void UpdateProcessCount(int id, int x)
        {
            if(x<0){return;}

            if(scheduleMap.find(id)!=scheduleMap.end())
            {
                totalProcesses-=scheduleMap[id];
                currProcesses-=scheduleMap[id];
                timesCalled[id]-=scheduleMap[id];
                if(x==0 && scheduleMap[id]!=0)
                {
                    currIds.erase(std::find(currIds.begin(),currIds.end(),id));
                }
            }
            else if(x!=0)
            {
                currIds.push_back(id);
            }
            scheduleMap[id]=x;
            timesCalled[id]+=x;
            totalProcesses+=x;
            currProcesses+=x;
            needUpdate=true;
        }
        int GetNextProcess()
        {
            if(currProcesses==0){return -1;}
            if(needUpdate)
            {
                std::sort(currIds.begin(), currIds.end(), [this](const int &a, const int &b)
                {
                    return (timesCalled[a] / totalProcesses) > (timesCalled[b] / totalProcesses);
                    //Determine scheduling using all time frequency of the process ID being added to the schedule, higher frequency = higher priority
                });
            }
            int outID=currIds[0];
            scheduleMap[outID]--;
            currProcesses--;
            if(scheduleMap[outID]==0)
            {
                currIds.erase(std::find(currIds.begin(),currIds.end(),outID));
            }
            needUpdate=false;
            return outID;
        }
        bool empty() { return currProcesses == 0; }
        int GetUniqueProcesses() const { return currIds.size(); }
        int GetCurrProcesses() const { return currProcesses; }
        int GetTotalProcesses() const { return totalProcesses; }

    };
}
#endif //PROJECT_CSE498_SPRING2025_GROUP_07_TEAM07LIBRARY_SCHEDULER_H
