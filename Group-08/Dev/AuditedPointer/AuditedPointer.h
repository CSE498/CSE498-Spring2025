#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

namespace cse {

#ifdef NDEBUG

// ==================== Non-Debug Mode (Raw Pointer) ====================

template <typename TYPE>
class Aptr
{
public:
    // Constructor
    explicit Aptr(TYPE* ptr = nullptr) : mPtr(ptr) {}

    // Copy constructor
    Aptr(const Aptr& other) : mPtr(new TYPE(*other.mPtr)) {}

    // Copy assignment operator
    Aptr& operator=(const Aptr& other)
    {
        if (this != &other) {
            delete mPtr;
            mPtr = new TYPE(*other.mPtr);
        }
        return *this;
    }

    // Move constructor
    Aptr(Aptr&& other) : mPtr(other.mPtr)
    {
        other.mPtr = nullptr;
    }

    // Move assignment operator
    Aptr& operator=(Aptr&& other)
    {
        if (this != &other) {
            delete mPtr;
            mPtr = other.mPtr;
            other.mPtr = nullptr;
        }
        return *this;
    }

    // Dereference operator
    TYPE& operator*() const { return *mPtr; }

    // Arrow operator
    TYPE* operator->() const { return mPtr; }

    // Check if the pointer is null
    explicit operator bool() const { return mPtr != nullptr; }

    // Delete the managed object
    void Delete()
    {
        delete mPtr;
        mPtr = nullptr;
    }

private:
    TYPE* mPtr;
};

// Stand-alone MakeAudited function
template <typename TYPE, typename... Args>
Aptr<TYPE> MakeAudited(Args&&... args)
{
    return Aptr<TYPE>(new TYPE(std::forward<Args>(args)...));
}

#else

// ==================== Debug Mode (Audited Pointer) ====================

// Global counter and LeakChecker
int globalCounter = 0; 

struct LeakChecker
{
    ~LeakChecker()
    {
        if (globalCounter != 0)
        {
            std::cerr << "Memory leak detected: " << globalCounter << " objects not deleted." << std::endl;
            std::terminate();
        }
    }
};

LeakChecker leakChecker; // Global instance of LeakChecker

template <typename TYPE>
class Aptr
{
public:
    // Constructor
    explicit Aptr(TYPE* ptr = nullptr) : mPtr(ptr)
    {
        if (mPtr)
        {
            ++globalCounter;
        }
    }

    // Copy constructor
    Aptr(const Aptr& other) : mPtr(other.mPtr ? new TYPE(*other.mPtr) : nullptr)
    {
        if (mPtr)
        {
            ++globalCounter;
        }
    }

    // Copy assignment operator
    Aptr& operator=(const Aptr& other)
    {
        if (this != &other)
        {
            if (mPtr)
            {
                --globalCounter;
            }
            delete mPtr;
            mPtr = other.mPtr ? new TYPE(*other.mPtr) : nullptr;
            if (mPtr)
            {
                ++globalCounter;
            }
        }
        return *this;
    }

    // Move constructor
    Aptr(Aptr&& other) : mPtr(other.mPtr)
    {
        other.mPtr = nullptr;
    }

    // Move assignment operator
    Aptr& operator=(Aptr&& other)
    {
        if (this != &other)
        {
            if (mPtr)
            {
                --globalCounter;
            }
            delete mPtr;
            mPtr = other.mPtr;
            other.mPtr = nullptr;
        }
        return *this;
    }

    // Dereference operator
    TYPE& operator*() const
    {
        if (!mPtr)
        {
            std::cerr << "Dereferencing a null pointer" << std::endl;
            std::terminate();
        }
        return *mPtr;
    }

    // Arrow operator
    TYPE* operator->() const
    {
        if (!mPtr)
        {
            std::cerr << "Accessing a null pointer" << std::endl;
            std::terminate();
        }
        return mPtr;
    }

    // Check if the pointer is null
    explicit operator bool() const
    {
        return mPtr != nullptr;
    }

    // Delete the managed object
    void Delete()
    {
        if (!mPtr)
        {
            std::cerr << "Deleting a null pointer" << std::endl;
            std::terminate();
        }
        --globalCounter;
        delete mPtr;
        mPtr = nullptr;
    }

    // Get the ID of this AuditedPointer
    int GetID() const
    {
        return 0;
    }

    // Get a set of all active AuditedPointer IDs and their pointers
    static std::unordered_map<int, void*> GetActiveAptrs()
    {
        return {};
    }
    
        // Find an AuditedPointer by ID in the active set
    static void* Find(int id)
    {
        return nullptr;
    }
    
    // Reset all active AuditedPointers (delete and clear the active set)
    static void Reset()
    {

    }

private:
    // Base raw pointer
    TYPE* mPtr;

    int mID;

};

// Stand-alone MakeAudited function
template <typename TYPE, typename... Args>
Aptr<TYPE> MakeAudited(Args&&... args)
{
    return Aptr<TYPE>(new TYPE(std::forward<Args>(args)...));
    ++globalCounter;
}

#endif

}