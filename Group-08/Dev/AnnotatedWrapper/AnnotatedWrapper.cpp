// AnnotatedWrapper.cpp
#include "AnnotatedWrapper.h"

void AnnotatedWrapper::addAnnotation(std::string key, std::any value) {
    annotations[key] = value;
    // Method code
}

/// used ChatGPT on this function
std::any AnnotatedWrapper::getAnnotation(std::string key) {
    auto it = annotations.find(key);
    if (it != annotations.end()) {
        return it->second;  // Return the stored std::any directly
    }
    return std::any{};
    
}

void AnnotatedWrapper::removeAnnotation(std::string key) {
    // Method code
    annotations.erase(key);
}

void AnnotatedWrapper::listAnnotations() {
    // Method code
    for (auto const& [key, val] : annotations) {
        std::cout << key << " : " << std::any_cast<std::string>(val) << std::endl;
    }
}

void AnnotatedWrapper::clearAnnotations() {
    // Method code
    annotations.clear();
}