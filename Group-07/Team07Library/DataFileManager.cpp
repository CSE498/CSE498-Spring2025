#include "DataFileManager.h"
#include <fstream> // https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-
#include <iostream>

namespace cse {
    // Load in path to file as a string
    // DataFileManager::DataFileManager(const std::string& path) : filePath(path) {}
    // DataFileManager::DataFileManager(const std::string& path) : filePath(path) {
    //    std::cout << "DataFileManager constructor called with path: " << path << std::endl;
    // }
    // Open CSV file based on location (path variable)
    void DataFileManager::openFile(const std::string& path) {
        // Check if we've already opened a file
        if (cse::DataFileManager::getFile() == "") {
        	std::cout << "Please close the current file before attempting to open a new one." << std::endl;
        }
        // Handles CSV Case, https://en.cppreference.com/w/cpp/string/basic_string/find_last_of
        else if (path.substr(path.find_last_of(".") + 1) == "csv") {
            cse::DataFileManager::setFile(path);
        	std::cout << "File has a .csv extension." << std::endl;
    	}
        // Handles Error
        else {
        	std::cout << "File extension is not valid." << std::endl;
    	}
    }

    // Updates the file based on provided functions and builds new rows
    void DataFileManager::update() {
        // Iterate over the unordered_map and call each function
        for (const auto& pair : functionMap) {
            std::cout << "Calling " << pair.first << std::endl;
            pair.second();  // Call the function
        }
    }

    void DataFileManager::addFunction(const std::string& name, const std::function<void()>& lambda){
        // functionMap[name] = lambda;  // Add the function to the map
        auto var1 = name;
        auto var2 = lambda;
    }

    void DataFileManager::closeFile() {

    }
}
