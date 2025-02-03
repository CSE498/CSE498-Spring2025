#ifndef DATAFILEMANAGER_H
#define DATAFILEMANAGER_H

#include <string>

class DataFileManager {
public:
    DataFileManager(const std::string& path); // Constructor
    void update();
    void openFile();
    void closeFile();
private:
    std::string filePath;
    // std::vector<>
};

#endif // DATAFILEMANAGER_H
