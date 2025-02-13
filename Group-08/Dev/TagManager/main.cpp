#include <iostream>
#include "TagManager.h"

int main () {
    TagManager tm;

     // Example usage
     tm.AddTag("CSE498", "urgent");
     tm.AddTag("CSE498", "work");
     tm.AddTag("FOR101", "urgent");
     tm.AddTag("KIN101", "personal");
 
     // Retrieve all tags for "item1"
     auto tags = tm.GetTags("CSE498");
     std::cout << "Tags for CSE498: ";
     for (const auto& tag : tags) {
         std::cout << tag << ", ";
     }
     std::cout << std::endl;
 
     // Retrieve all entries for "urgent" tag
     auto tasks = tm.GetTaskTags("urgent");
     std::cout << "Entries with 'urgent' tag: ";
     for (const auto& task : tasks) {
         std::cout << task << ", ";
     }
     std::cout << std::endl;
 
     // Check if "item1" has "work" tag
     std::cout << "Does CSE498 have 'work' tag? " << (tm.HasTag("CSE498", "work") ? "Yes" : "No") << std::endl;
 
     // Remove tag from entry
     tm.RemoveTag("CSE498", "work");
 
     // Retrieve all tags for "item1" after removal
     tags = tm.GetTags("CSE498");
     std::cout << "Tags for CSE498 after removing 'work': ";
     for (const auto& tag : tags) {
         std::cout << tag << " ";
     }
     std::cout << std::endl;
 
     // Clear all tags from "item1"
     tm.ClearTagsForTask("CSE498");
 
     // Verify tags for "item1" after clearing
     tags = tm.GetTaskTags("CSE498");
     std::cout << "Tags for CSE498 after clearing: ";
     for (const auto& tag : tags) {
         std::cout << tag << " ";
     }
     std::cout << std::endl;

    return 0;
}