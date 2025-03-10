/**
 * @file FunctionSet.h
 * @author jiang
 */

#ifndef FUNCTIONSET_H
#define FUNCTIONSET_H

#include <vector>
#include <functional>
#include <type_traits>
#include <stdexcept>


/**
 * @brief A container that holds multiple callable objects sharing the same signature
 *        and can invoke them all using a single call.
 *
 * @param R    The return type of the functions.
 * @param Args The argument types of the functions.
 */
namespace cse
{
    template <typename R, typename... Args>
    class FunctionSet
    {
    public:
        using FunctionType = std::function<R(Args...)>;

        /// Constructor
        FunctionSet();
        /// Destructor
        ~FunctionSet();

        /**
         * @brief Add a function to the set
         * @param func The actual function to store
         */
        void AddFunction(const FunctionType& func);



        /**
         * @brief Clear all the functions in the function set
         */
        void ClearAll();

        /**
         * @brief Check if the set is empty
         * @return true if empty; false otherwise
         */
        bool IsEmpty() const;

        /**
         * @brief Return the size of the function set
         * @return number of functions stored
         */
        std::size_t CountFun() const;

        /**
         * @brief Return the index number of the function and use it for later. (This only works for real function pointers or non-capturing lambdas )
         * @param func the actual function
         * @return a int that tells the position of the function
         */
        int FindFunctionIndex(const FunctionType& func) const;

        /**
         * @brief Remove a function from the set (by reference).
         *        Real usage may require a different approach, because std::function
         *        doesn't have operator== for comparing contents.
         * @param func the actual function
         */
        void RemoveFunction(const FunctionType& func);

        /**
         * @brief Call all functions in the set with the given arguments
         * @param args The parameters to pass to each function
         * @return Depending on R, returns either std::vector<R> or void
         */
        auto CallAll(Args... args)
        {
            return callAllImpl(std::is_void<R>{}, args...);
        }

    private:
        std::vector<FunctionType> mFunctions;

        /// If R is not void, we collect results in std::vector<R>.
        template <typename... CallArgs>
        std::vector<R> callAllImpl(std::false_type, CallArgs&&... callArgs)
        {
            std::vector<R> results;
            results.reserve(mFunctions.size());
            for (auto &func : mFunctions)
            {
                results.push_back(func(std::forward<CallArgs>(callArgs)...));
            }
            return results;
        }

        /// If R is void, we just call the functions with no return.
        template <typename... CallArgs>
        void callAllImpl(std::true_type, CallArgs&&... callArgs)
        {
            for (auto &func : mFunctions)
            {
                func(std::forward<CallArgs>(callArgs)...);
            }
        }
    };
}

#endif // FUNCTIONSET_H
