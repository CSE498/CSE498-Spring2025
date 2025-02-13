#ifndef ANNOTATEDWRAPPER_H
#define ANNOTATEDWRAPPER_H

#include <iostream>
#include <unordered_map>
#include <any>

class AnnotatedWrapper {
public:
    // Constructor
    AnnotatedWrapper(){
        annotations = std::unordered_map<std::string, std::string>();
    };

    // Destructor
    // ~AnnotatedWrapper() = default;

    // Public methods
    void addAnnotation( const std::string& key, const std::string& value);
    std::string getAnnotation(const std::string key);
    void removeAnnotation(const std::string key);
    void listAnnotations();
    void clearAnnotations();

private:
    std::unordered_map<std::string, std::string> annotations;

};

#endif // ANNOTATEDWRAPPER_H