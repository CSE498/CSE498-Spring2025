#ifndef ANNOTATEDWRAPPER_H
#define ANNOTATEDWRAPPER_H

#include <iostream>
#include <unordered_map>
#include <any>


 /**
 * @class AnnotatedWrapper
 * @brief A wrapper class for managing key-value annotations.
 *
 * This class provides an easy-to-use interface for adding, retrieving,
 * and removing key-value annotations. It is designed to be lightweight 
 * and efficient using `std::unordered_map` for fast lookups.
 *
 * Internally:
 * - Uses `std::unordered_map<std::string, std::string>` to store 
 *   annotations as key-value pairs.
 *
 */
namespace cse {

    class AnnotatedWrapper {
    public:
        // Constructor
        AnnotatedWrapper(){
            mAnnotations = std::unordered_map<std::string, std::string>();
        };
        // Destructor
        // ~AnnotatedWrapper() = default;

        // Public methods
        void addAnnotation( const std::string& key, const std::string& value);

        // Temporary hard coded annotation types for testing only
        void addAnnotation( const std::string& wrapperKey, const std::string& personalKey, const std::string& value);
        void addAnnotation( const std::string& key, const float number);

        std::string getAnnotation(const std::string key);
        void removeAnnotation(const std::string key);
        void listAnnotations();
        void clearAnnotations();

        void setFontSize(float size);
        float getFontSize();

        void setFontColor(const std::string& color);
        const std::string& getFontColor();

        void setBackgroundColor (const std::string& color);
        const std::string& getBackgroundColor();

        int getAnnotationCount();

    private:
        std::unordered_map<std::string, std::string> mAnnotations;

        int mFontSize;
        int mFontColor;
        int mBackgroundColor;

    };
}

#endif // ANNOTATEDWRAPPER_H