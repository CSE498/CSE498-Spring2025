//
// Created by Kelsi Elliott on 2/3/25.
//

#ifndef TAGMANAGER_TAGMANAGER_H
#define TAGMANAGER_TAGMANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class TagManager {
private:
    // Maps from task -> set of tags, and from tag -> set of task
    std::unordered_map<std::string, std::unordered_set<std::string> > TaskToTag;
    std::unordered_map<std::string, std::unordered_set<std::string> > TagToTasks;

public:
    // 1. Adds a tag to the task
    void AddTag(const std::string& task, const std::string& tag);

    // 2. Removes a tag from the task
    void RemoveTag(const std::string& task, const std::string& tag);

    // 3. Retrieves all tags associated with a task
    std::unordered_set<std::string> GetTags(const std::string& task);

    // 4. Retrieves all tasks associated with a specific tag
    std::unordered_set<std::string> GetTasks(const std::string& tag);

    // 5. Clears all tags for a specific task
    void ClearTaskTags(const std::string& task);

    // 6. Clears all tasks associated with a specific tag
    void ClearTagTasks(const std::string& tag);

    // 7. Checks if an tasks has a specific tag
    bool HasTag(const std::string& task, const std::string& tag);
};


#endif //TAGMANAGER_TAGMANAGER_H
