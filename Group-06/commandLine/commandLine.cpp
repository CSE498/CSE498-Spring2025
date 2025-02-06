#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace cse {

    /**
     * @brief A class for managing command line operations
     * 
     */
    class commandLine {
    public:

        /**
         * @brief Adds a command to the command map
         * 
         * @param command The command string
         * @param func The function to be executed for the command
         */
        void addCommand(const std::string& command, std::function<void()> func) {
            // Add command to the map
            commands[command] = func;
        }

        /**
         * @brief Executes a command if it exists in the command map
         * 
         * @param command The command string to be executed
         */
        void executeCommand(const std::string& command) {
            // Execute the command if it exists
            if (commands.find(command) != commands.end()) {
                commands[command]();
            } else {
                std::cout << "Unknown command: " << command << std::endl;
            }
        }

        /**
         * @brief Tracks the history of executed commands
         * 
         * @param command The command string to be tracked
         */
        void trackHistory(const std::string& command) {
            // Track command history
            history.push_back(command);
        }

        /**
         * @brief Prints the history of executed commands
         * 
         */
        void printHistory() const {
            // Print command history
            for (const auto& cmd : history) {
                std::cout << cmd << std::endl;
            }
        }

        /**
         * @brief Tracks the current state
         * 
         * @param state The state string to be tracked
         */
        void trackState(const std::string& state) {
            // Track state
            currentState = state;
        }

        /**
         * @brief Gets the current state
         * 
         * @return std::string The current state
         */
        std::string getState() const {
            // Get current state
            return currentState;
        }

    private:
        std::unordered_map<std::string, std::function<void()>> commands; // Map of commands to functions
        std::vector<std::string> history; // Vector of command history
        std::string currentState; // Current state
    };

}