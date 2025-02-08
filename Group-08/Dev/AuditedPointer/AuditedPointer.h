#pragma once

#include <iostream>
#include <unordered_set>
#include <memory>

#ifdef DNDEBUG

// ==================== Non-Debug Mode (Raw Pointer) ====================

template <typename TYPE>
class Aptr
{
public:
    // Constructor
    explicit Aptr(TYPE* ptr = nullptr) : mPtr(ptr) {}

    // Destructor
    ~Aptr() { delete mPtr; }

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
    Aptr(Aptr&& other) noexcept : mPtr(other.mPtr)
    {
        other.mPtr = nullptr;
    }

    // Move assignment operator
    Aptr& operator=(Aptr&& other) noexcept
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

template <typename TYPE>
class Aptr
{
public:
    // Constructor
    explicit Aptr(TYPE* ptr = nullptr);

    // Destructor
    ~Aptr();

    // Copy constructor
    Aptr(const Aptr& other);

    // Copy assignment operator
    Aptr& operator=(const Aptr& other);

    // Move constructor
    Aptr(Aptr&& other) noexcept;

    // Move assignment operator
    Aptr& operator=(Aptr&& other) noexcept;

    // Dereference operator
    TYPE& operator*() const;

    // Arrow operator
    TYPE* operator->() const;

    // Check if the pointer is null
    explicit operator bool() const;

    // Delete the managed object
    void Delete();

    // Function to check for leaks
    static void CheckForLeaks();

private:
    // Base raw pointer
    TYPE* mPtr;

    // Set of pointers in the program to check for leaks
    static std::unordered_set<TYPE*> mTrackedPointers;
};

// Stand-alone MakeAudited function
template <typename TYPE, typename... Args>
Aptr<TYPE> MakeAudited(Args&&... args);

// Global object to check for leaks at program exit
struct LeakChecker
{
    ~LeakChecker();
};

LeakChecker leakChecker;

// ==================== Template Implementations ====================

// Allocates memory for the set of tracked pointers
template <typename TYPE>
std::unordered_set<TYPE*> Aptr<TYPE>::mTrackedPointers;

// Constructor
// ex: Aptr<Example> ptr(new Example()); 
//// Creates an Aptr managing a new Example object
template <typename TYPE>
Aptr<TYPE>::Aptr(TYPE* ptr) : mPtr(ptr)
{
    if (mPtr)
    {
        mTrackedPointers.insert(mPtr);
    }
}

// Destructor
template <typename TYPE>
Aptr<TYPE>::~Aptr()
{
    if (mPtr)
    {
        mTrackedPointers.erase(mPtr);
    }
    delete mPtr;
}

// Copy constructor
// ex: Aptr<Example> ptr2(ptr1); 
//// Creates a copy of `ptr1` (both manage the same Example object)
template <typename TYPE>
Aptr<TYPE>::Aptr(const Aptr& other) : mPtr(other.mPtr)
{
    if (mPtr)
    {
        mTrackedPointers.insert(mPtr);
    }
}

// Copy assignment operator
// ex Aptr<Example> ptr2 = ptr1; 
//// Copies `ptr1` into `ptr2` (both manage the same Example object)
template <typename TYPE>
Aptr<TYPE>& Aptr<TYPE>::operator=(const Aptr& other)
{
    if (this != &other)
    {
        if (mPtr)
        {
            mTrackedPointers.erase(mPtr);
        }
        if (other.mPtr)
        {
            mTrackedPointers.insert(other.mPtr);
        }
        delete mPtr;
        mPtr = other.mPtr;
    }
    return *this;
}

// Move constructor
// ex: Aptr<Example> ptr2(std::move(ptr1)); 
//// Moves ownership from `ptr1` to `ptr2` (ptr1 becomes null)
template <typename TYPE>
Aptr<TYPE>::Aptr(Aptr&& other) noexcept : mPtr(other.mPtr)
{
    other.mPtr = nullptr;
}

// Move assignment opoerator
// Aptr<Example> ptr2 = std::move(ptr1); 
//// Moves ownership from `ptr1` to `ptr2` (ptr1 becomes null)
template <typename TYPE>
Aptr<TYPE>& Aptr<TYPE>::operator=(Aptr&& other) noexcept
{
    if (this != &other)
    {
        if (mPtr)
        {
            mTrackedPointers.erase(mPtr);
        }
        delete mPtr;
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }
    return *this;
}

// Dereference operator
// ex: Example obj = *ptr; 
//// Dereferences `ptr` to access the managed Example object
template <typename TYPE>
TYPE& Aptr<TYPE>::operator*() const
{
    if (!mPtr || mTrackedPointers.find(mPtr) == mTrackedPointers.end())
    {
        std::cerr << "Dereferencing a deleted or null pointer" << std::endl;
        std::terminate();
    }
    return *mPtr;
}

// Arrow operator
// ex: ptr->doSomething(); 
//// Accesses a member function or variable of the managed Example object
template <typename TYPE>
TYPE* Aptr<TYPE>::operator->() const
{
    if (!mPtr || mTrackedPointers.find(mPtr) == mTrackedPointers.end())
    {
        std::cerr << "Accessing a deleted or null pointer" << std::endl;
        std::terminate();
    }
    return mPtr;
}

// Checks if there is a ptr within the object
template <typename TYPE>
Aptr<TYPE>::operator bool() const
{
    return mPtr != nullptr;
}

// Member function to delete the object
template <typename TYPE>
void Aptr<TYPE>::Delete()
{
    if (!mPtr || mTrackedPointers.find(mPtr) == mTrackedPointers.end())
    {
        std::cerr << "Deleting a deleted or null pointer" << std::endl;
        std::terminate();
    }
    mTrackedPointers.erase(mPtr);
    delete mPtr;
    mPtr = nullptr;
}

// Function ran at runtime that checks in DEBUG mode if
// all instances of the class are deleted
template <typename TYPE>
void Aptr<TYPE>::CheckForLeaks()
{
    if (!mTrackedPointers.empty())
    {
        std::cerr << "Memory leak detected: " << mTrackedPointers.size() << " pointers not deleted." << std::endl;
        std::terminate();
    }
}

// MakeAudited helper function to turn classes to Aptrs
template <typename TYPE, typename... Args>
Aptr<TYPE> MakeAudited(Args&&... args)
{
    // std::forward ensures lvalues and rvalues and perserved
    return Aptr<TYPE>(new TYPE(std::forward<Args>(args)...));
}

// LeakChecker destructor
LeakChecker::~LeakChecker()
{
    Aptr<int>::CheckForLeaks(); // Use int as a placeholder type
}

#endif