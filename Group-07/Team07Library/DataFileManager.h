#ifndef DATAFILEMANAGER_H
#define DATAFILEMANAGER_H

#include <string>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>

namespace cse {
    class DataFileManager {
    private:
        // Easiest way to store functions is through an unordered map
        // https://stackoverflow.com/questions/55520876/creating-an-unordered-map-of-stdfunctions-with-any-arguments
        std::unordered_map<std::string, std::function<void()>> functionMap;

        // Track status of file and updates made
        std::string fileOpened = "";
        bool updateMade = false;
    public:
        // Constructors
        DataFileManager() = default;
        ~DataFileManager() = default;

        // Getter and Setter for our file location
        const std::string& getFile(){
            return fileOpened;
        }

        void setFile(const std::string& path){
            fileOpened = path;
        }

        void openFile(const std::string& path);
        void update();
        void addFunction(const std::string& name, const std::function<void()>& lambda);

        // Delete a function from our map
        void deleteFunction(const std::string& name){
            // https://cplusplus.com/reference/unordered_map/unordered_map/erase/
            auto it = functionMap.find(name);
            if (it != functionMap.end()) {
                functionMap.erase(it);
            }
        }

        // List each function we have stored so far
        void listFunctions(){
            // https://stackoverflow.com/questions/22880431/iterate-through-unordered-map-c
            for (const auto & [ key, value ] : functionMap) {
                // Read in and assert Substring
                std::istringstream iss(key);
                std::string first, second;
                iss >> first;
                iss >> second;
                // Condition to assert
                bool condition = (second == "Value");
                // Use assert to test the condition
                assert(condition && "String does not match the expected value.");
                // If the condition is true, this line will be executed
                std::cout << "Assertion passed!" << std::endl;
                std::cout << key << std::endl;
            }
        }
        // Clear every function
        void clearFunctions(){
            functionMap.clear();
        }

        void closeFile();

    };
}
#endif // DATAFILEMANAGER_H
