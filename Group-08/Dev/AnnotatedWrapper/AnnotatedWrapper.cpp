// AnnotatedWrapper.cpp
#include "AnnotatedWrapper.h"

// void AnnotatedWrapper::addAnnotation(std::string key, std::any value) {
//     annotations[key] = value;
//     // Method code
// }

// /// used ChatGPT on this function
// std::any AnnotatedWrapper::getAnnotation(std::string key) {
//     auto it = annotations.find(key);
//     if (it != annotations.end()) {
//         return it->second;  // Return the stored std::any directly
//     }
//     return std::any{};
    
// }




void AnnotatedWrapper::addAnnotation(const std::string& key, const std::string& value) {
    annotations[key] = value;
    // Method code
}

/// used ChatGPT on this function
std::string AnnotatedWrapper::getAnnotation(const std::string key) {
    return annotations.at(key);
    // auto it = annotations.find(key);
    // if (it != annotations.end()) {
    //     return it->second;  // Return the stored std::any directly
    // }
    // return "";
    // return std::any{};
    
}

void AnnotatedWrapper::removeAnnotation(const std::string key) {
    // Method code
    annotations.erase(key);
}

void AnnotatedWrapper::listAnnotations() {
    if (annotations.empty()) {
        std::cout << "No annotations to list" << std::endl;
        return;
    } else {
        for (const auto& pair : annotations) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }
    
    // Method code
    // for (auto const& [key, val] : annotations) {
    //     std::cout << key << " : " << std::any_cast<std::string>(val) << std::endl;
    // }

    // for (auto const& [key, val] : annotations) {
    //     std::cout << key << " : " << val << std::endl;
    // }
}

void AnnotatedWrapper::clearAnnotations() {
    // Method code
    annotations.clear();
}