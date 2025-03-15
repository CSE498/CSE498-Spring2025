#include "AnnotatedWrapper.h"
#include <string>
using namespace std;

int main()
{
    AnnotatedWrapper aw = AnnotatedWrapper();

    aw.addAnnotation("input", "output");
    aw.addAnnotation("key2", "value2");
    aw.addAnnotation("key3", "value3");

    aw.listAnnotations();

    std::cout << "Value of input: " << aw.getAnnotation("input") << std::endl;
    std::cout << "Value of key2: " << aw.getAnnotation("key2") << std::endl;
    std::cout << "Value of key3: " << aw.getAnnotation("key3") << std::endl;

    aw.removeAnnotation("key2");
    aw.listAnnotations();

    aw.clearAnnotations();

    std::cout << "Annotations after clearing: " << std::endl;
    aw.listAnnotations();

    // std::cout << "Hello World" << std::endl;
    return 0;
}