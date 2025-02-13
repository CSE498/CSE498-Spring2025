#include "TagManager.h"
using std::string;

/**
 * Adds a tag to a task
 * 
 * @param task
 * @param tag
 */
void TagManager::AddTag(const string& task, const string& tag) {
    TaskToTag[task].insert(tag);  // Add tag to task
    TagToTask[tag].insert(task);  // Add task to tag
}

/**
 * Removes a tag from a task
 * 
 * @param task
 * @param tag
 */
void TagManager::RemoveTag(const string& task, const string& tag) {
    auto taskIt = TaskToTag.find(task);
    if (taskIt != TaskToTag.end()) {
        taskIt->second.erase(tag);  // Remove tag from task
        if (taskIt->second.empty()) {
            TaskToTag.erase(task);  // If no more tags, remove task
        }
    }

    auto tag_it = TagToTask.find(tag);
    if (tag_it != TagToTask.end()) {
        tag_it->second.erase(task);  // Remove task from tag
        if (tag_it->second.empty()) {
            TagToTask.erase(tag);  // If no more entries, remove tag
        }
    }
}

/**
 * Return all the tags 
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
std::unordered_set<string> TagManager::GetTags(const string& task) {
    auto it = TaskToTag.find(task);
    if (it != TaskToTag.end()) {
        return it->second;  // Return the set of tags
    }
    return std::unordered_set<string>();  // Return empty set if no tags are found
}

/**
 * Return all the tags associated with the task
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
std::unordered_set<string> TagManager::GetTaskTags(const string& tag) {
    auto it = TagToTask.find(tag);
    if (it != TagToTask.end()) {
        return it->second;  // Return the set of entries
    }
    return std::unordered_set<string>();  // Return empty set if no entries are found
}

/**
 * Clears all the tags associated with the task
 * 
 * @param task
 */
void TagManager::ClearTagsForTask(const string& task) {
    auto it = TaskToTag.find(task);
    if (it != TaskToTag.end()) {
        // For each tag, remove the task from the tag's set
        for (const string& tag : it->second) {
            TagToTask[tag].erase(task);
            if (TagToTask[tag].empty()) {
                TagToTask.erase(tag);  // Remove tag if no entries are left
            }
        }
        TaskToTag.erase(task);  // Remove all tags for this task
    }
}

/**
 * Clears all the tags associated with a specific tag
 * 
 * @param tag
 */
void TagManager::ClearTags(const string& tag) {
    auto it = TagToTask.find(tag);
    if (it != TagToTask.end()) {
        // For each task, remove the tag from its set of tags
        for (const string& task : it->second) {
            TaskToTag[task].erase(tag);
            if (TaskToTag[task].empty()) {
                TaskToTag.erase(task);  // Remove task if no tags are left
            }
        }
        TagToTask.erase(tag);  // Remove all entries for this tag
    }
}

/**
 * Checks if a task has a specific tag
 * 
 * @param task
 * @return bool 
 */
bool TagManager::HasTag(const string& task, const string& tag) {
    auto it = TaskToTag.find(task);
    if (it != TaskToTag.end()) {
        return it->second.find(tag) != it->second.end();  // Check if tag exists
    }
    return false;  // Return false if task doesn't exist
}