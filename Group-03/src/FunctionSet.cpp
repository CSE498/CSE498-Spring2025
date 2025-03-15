/**
 * @file FunctionSet.cpp
 * @author jiang
 */

#include "FunctionSet.h"

#include <iostream>
#include <string>


/**
 * Constructor
 */
template <typename R, typename... Args>
cse::FunctionSet<R, Args...>::FunctionSet() = default;

/**
 * Destructor
 */
template <typename R, typename... Args>
cse::FunctionSet<R, Args...>::~FunctionSet() = default;

/**
 * addFunction
 */
template <typename R, typename... Args>
void cse::FunctionSet<R, Args...>::AddFunction(const FunctionType& func)
{
    if (func == nullptr){
      std::cerr << "Function does not exist" << std::endl;
      return;
    }
    using PointerType = R(*)(Args...);

    if (func.target_type() == typeid(PointerType)) {
        const PointerType* fp = func.template target<PointerType>();
        if (fp) {
            std::cout << "addFunction storing: " << (void*)(*fp) << std::endl;
        }
    }

    mFunctions.push_back(func);
}



/**
 * clearAll
 */
template <typename R, typename... Args>
void cse::FunctionSet<R, Args...>::ClearAll()
{
    mFunctions.clear();
}

/**
 * isEmpty
 */
template <typename R, typename... Args>
bool cse::FunctionSet<R, Args...>::IsEmpty() const
{
    return mFunctions.empty();
}

/**
 * countFunSet
 */
template <typename R, typename... Args>
std::size_t cse::FunctionSet<R, Args...>::CountFun() const
{
    return mFunctions.size();
}

/**
 * Find the index of the function
 */
template <typename R, typename... Args>
int cse::FunctionSet<R, Args...>::FindFunctionIndex(const FunctionType& func) const
{
    if (func == nullptr){
        std::cerr << "Are you really trying to find an empty function? Really?" << std::endl;
        return -1;
    }
    using PointerType = R(*)(Args...);

    if (func.target_type() == typeid(PointerType))
    {
        const PointerType* funcPtr = func.template target<PointerType>();
        if (!funcPtr) return -1;

        for (int i = 0; i < static_cast<int>(mFunctions.size()); ++i)
        {
            const auto& storedFunc = mFunctions[i];
            if (storedFunc.target_type() == typeid(PointerType))
            {
                const PointerType* storedPtr = storedFunc.template target<PointerType>();
                if (storedPtr && *storedPtr == *funcPtr)
                {
                    return i;
                }
            }
        }
    }
    std::cerr << "Function does not exist in the set" << std::endl;
    return -1;
}



/**
 * removeFunction
 */
template <typename R, typename... Args>
void cse::FunctionSet<R, Args...>::RemoveFunction( const FunctionType& func)
{
    if (func == nullptr){
        std::cerr << "Are you really trying to remove an empty function? Really?" << std::endl;
        return;
    }
    int index = FindFunctionIndex(func);
    if (index >= 0)
    {
        mFunctions.erase(mFunctions.begin() + index);
        std::cerr << "Function is removed, hopfully." << std::endl;
    }
}
template class cse::FunctionSet<int, int>;                  /// For "FunctionSet<int,int>"
template class cse::FunctionSet<void, const std::string&>;  /// For "FunctionSet<void, const std::string&>"
