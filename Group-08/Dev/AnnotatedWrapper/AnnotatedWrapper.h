#ifndef ANNOTATEDWRAPPER_H
#define ANNOTATEDWRAPPER_H

#include <iostream>
#include <map>
#include <any>

class AnnotatedWrapper {
public:
    // Constructor
    AnnotatedWrapper() = default;

    // Destructor
    ~AnnotatedWrapper() = default;

    // Public methods
    void addAnnotation( std::string key, std::any value);
    std::any getAnnotation(std::string key);
    void removeAnnotation(std::string key);
    void listAnnotations();
    void clearAnnotations();

private:
    std::unordered_map<std::string, std::any> annotations;

};

#endif // ANNOTATEDWRAPPER_H