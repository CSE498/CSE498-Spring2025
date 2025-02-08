#include "TagManager.h"

using std::string;
using std::unordered_set;

/**
 * Adds a tag to a task
 * 
 * @param task
 * @param tag
 */
void TagManager::AddTag(const string& task, const string& tag) {
    TaskToTag[task].insert(tag);
    TagToTasks[tag].insert(task);
}

/**
 * Removes a tag from a task
 * 
 * @param task
 * @param tag
 */
void TagManager::RemoveTag(const string& task, const string& tag) {
    auto it = TaskToTag.find(task);

    if (it != TaskToTag.end()) {
        it->second.erase(tag);  //Remove tag from task
        if (it->second.empty()) {
            TaskToTag.erase(task);
        }
    }

    auto tag_it = TagToTasks.find(tag);
    if (tag_it != TagToTasks.end()) {
        tag_it->second.erase(task);  // Remove task from tag
        if (tag_it->second.empty()) {
            TagToTasks.erase(tag);  // If no more entries, remove tag
        }
    }
}

/**
 * Return all the tags 
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
unordered_set<string> TagManager::GetTags(const string& task) {
    auto it = TaskToTag.find(task);

    if(it != TaskToTag.end()) {
        return it->second;  //Return the set of tags
    }
    return unordered_set<string> (); //Return empty if no tags are found
}

/**
 * Return all the tags associated with the task
 * 
 * @param task
 * @return tags --> retrun empty set if no
 */
unordered_set<string> TagManager::GetTasks(const string& tag) {
    auto it = TagToTasks.find(tag);
    if (it != TagToTasks.end()) {
        return it->second;  // Return the set of entries
    }

    return unordered_set<string> (); //Return empty if no tasks are found
}


/**
 * Clears all the tags associated with the task
 * 
 * @param task
 */
void TagManager::ClearTaskTags(const std::string &task)
{
    auto it = TaskToTag.find(task);
    if (it != TaskToTag.end()) {
        // For each tag, remove the task from the tag's set
        for (const std::string& tag : it->second) {
            TagToTasks[tag].erase(task);
            if (TagToTasks[tag].empty()) {
                TagToTasks.erase(tag);  // Remove tag if no entries are left
            }
        }
        TaskToTag.erase(task);  // Remove all tags for this task
    }
}

/**
 * Clears all the tasks associated with a specific tag
 *
 * @param tag
 */
void TagManager::ClearTagTasks(const std::string &tag)
{
    auto it = TagToTasks.find(tag);
    if (it != TagToTasks.end()) {
        // For each task, remove the tag from its set of tags
        for (const std::string& task : it->second) {
            TaskToTag[task].erase(tag);
            if (TaskToTag[task].empty()) {
                TaskToTag.erase(task);  // Remove task if no tags are left
            }
        }
        TagToTasks.erase(tag);  // Remove all entries for this tag
    }
}

/**
 * Checks if a task has a specific tag
 * 
 * @param task
 * @return bool 
 */
bool TagManager::HasTag(const std::string &task, const std::string &tag)
{
    auto it = TaskToTag.find(task);
    if (it != TaskToTag.end()) {
        return it->second.find(tag) != it->second.end();  // Check if tag exists
    }
    return false;  // Return false if task doesn't exist
}
