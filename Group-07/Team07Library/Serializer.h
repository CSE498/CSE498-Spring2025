/**
 * @file Serializer.h
 * @author tdkduong
 */

#ifndef CSE_SERIALIZER_H
#define CSE_SERIALIZER_H

#include <iostream>
#include <fstream>
#include <string>

namespace cse
{
    // The mode in which the serializer operates.
    enum class Mode
    {
        SAVE,
        LOAD
    };
    class Serializer
    {
    public:
        // Constructor
        Serializer(Mode mode);
        // Generic Serialize and Deserialze method for simple types, based on current mode
        template <typename T>
        void Serialize(T &data, const std::string &filename);

    private:
        Mode mode_;
    };
} // namespace cse

namespace cse
{
    Serializer::Serializer(Mode mode)
        : mode_(mode) {}
    template <typename T>
    void Serializer::Serialize(T &data, const std::string &filename)
    {
        if (mode_ == Mode::SAVE)
        {
            std::ofstream OutFile(filename, std::ios::binary);
            if (!OutFile)
            {
                std::cerr << "Error opening file for writing: " << filename << std::endl;
                return;
            }
            OutFile.write(reinterpret_cast<const char *>(&data), sizeof(T));
            OutFile.close();
        }
        else if (mode_ == Mode::LOAD)
        {
            {
                std::ifstream InFile(filename, std::ios::binary);
                if (!InFile)
                {
                    std::cerr << "Error opening file for reading: " << filename << std::endl;
                    return;
                }
                InFile.read(reinterpret_cast<char *>(&data), sizeof(T));
                InFile.close();
            }
        }
    }
}

#endif // CSE_SERIALIZER_H