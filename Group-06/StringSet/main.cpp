#include "StringSet.h"
#include <iostream>

int main() {
    cse::StringSet set1, set2;

    set1.insert("yellow");
    set1.insert("blue");
    set1.insert("black");

    set2.insert("yellow");
    set2.insert("blue");
    set2.insert("purple");

    std::cout << "Size for set1: " << set1.size() << "(yellow, blue and black)" << std::endl;
    std::cout << "Size for set2: " << set2.size() << "(yellow, blue and purple)" << std::endl;

    cse::StringSet setUnion = set1.Union(set2);
    std::cout << "Size of Union Set: " << setUnion.size() << "(yellow, blue, black and purple)" << std::endl;

    cse::StringSet setIntersection = set1.Intersection(set2);
    std::cout << "Size of Intersection set: " << setIntersection.size() << "(yellow and blue)" << std::endl;

    set1.clear();
    std::cout << "check if .clear() make our set empty: " << set1.size() << "(size)" << std::endl;
    std::cout << set1.empty() << std::endl;

    set2.erase("blue");
    std::cout << "check if .erase() deleted blue from the set2: " << set2.size() << "(yellow and purple)" << std::endl;
}
