#include "TagManager.h"
using std::string;

namespace cse {
/**
 * Adds a tag to a task
 * 
 * @param task
 * @param tag
 */
void TagManager::AddTag(const string& task, const string& tag) {
    mTaskToTag[task].insert(tag);  // Add tag to task
    mTagToTask[tag].insert(task);  // Add task to tag
}

/**
 * Removes a tag from a task
 * 
 * @param task
 * @param tag
 */
void TagManager::RemoveTag(const string& task, const string& tag) {
    auto taskIt = mTaskToTag.find(task);
    if (taskIt != mTaskToTag.end()) {
        taskIt->second.erase(tag);  // Remove tag from task
        if (taskIt->second.empty()) {
            mTaskToTag.erase(task);  // If no more tags, remove task
        }
    }

    auto tag_it = mTagToTask.find(tag);
    if (tag_it != mTagToTask.end()) {
        tag_it->second.erase(task);  // Remove task from tag
        if (tag_it->second.empty()) {
            mTagToTask.erase(tag);  // If no more entries, remove tag
        }
    }
}

/**
 * Return all the tags 
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
std::unordered_set<string> TagManager::GetTags(const string& task) const {
    auto it = mTaskToTag.find(task);
    if (it != mTaskToTag.end()) {
        return it->second;  // Return the set of tags
    }
    return std::unordered_set<string>();  // Return empty set if no tags are found
}

/**
 * Return all the tags associated with all the tasks
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
std::unordered_set<string> TagManager::GetTaskTags(const string &tag) const {
    auto it = mTagToTask.find(tag);
    if (it != mTagToTask.end()) {
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
    auto it = mTaskToTag.find(task);
    if (it != mTaskToTag.end()) {
        // For each tag, remove the task from the tag's set
        for (const string& tag : it->second) {
            mTagToTask[tag].erase(task);
            if (mTagToTask[tag].empty()) {
                mTagToTask.erase(tag);  // Remove tag if no entries are left
            }
        }
        mTaskToTag.erase(task);  // Remove all tags for this task
    }
}

/**
 * Clears all the tags associated with a specific tag
 * 
 * @param tag
 */
void TagManager::ClearTags(const string& tag) {
    auto it = mTagToTask.find(tag);
    if (it != mTagToTask.end()) {
        // For each task, remove the tag from its set of tags
        for (const string& task : it->second) {
            mTaskToTag[task].erase(tag);
            if (mTaskToTag[task].empty()) {
                mTaskToTag.erase(task);  // Remove task if no tags are left
            }
        }
        mTagToTask.erase(tag);  // Remove all entries for this tag
    }
}

/**
 * Checks if a task has a specific tag
 * 
 * @param task
 * @return bool 
 */
bool TagManager::HasTag(const string& task, const string& tag) const {
    auto it = mTaskToTag.find(task);
    if (it != mTaskToTag.end()) {
        return it->second.find(tag) != it->second.end();  // Check if tag exists
    }
    return false;  // Return false if task doesn't exist
};

}   //namespace