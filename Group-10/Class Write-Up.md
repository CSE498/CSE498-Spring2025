## StaticVector 


### Class Description

Like the standard Vector, however the maximum vector size is specified in the template parameter and all memory for the vector is allocated at object creation. The size cannot go over the static limit.


### Similar Classes

Std::vector

std::array


### Key Functions

get_max_size() - Returns max size set at initialization

push_back() - Adds an element to the vector if there is enough space

Most standard vector functions - To replicate a standard vector’s behavior


### Error Conditions



1. Trying to push back when already at capacity. - User Error, can be handled by throwing an exception
2. Indexing past the length of the vector


### Expected Challenges



* Replicating most of the functions of a normal vector while maintaining the size restrictions


### External Helpful Classes

AuditedVector

AuditedArray


## MemoFunction


### Class Description

This class is a function wrapper that memoizes the results of that given function. It stores the parameters and the output on its first encounter for future uses and will be implemented to work on multi-parameter functions as well.


### Similar Classes

std::function


### Key Functions

constructor(function) - Stores the target function for the inputs and outputs

calculate(inputs) - Looks for cached output, otherwise uses the function to return the output

operator() overload

clear() - clears cache

cacheSize() - returns the size of the cache.


### Error Conditions



1. Output is too large to cache
2. Cache grows too large.


### Expected Challenges



* Implementing functionality with multiple parameters.
* Deciding which values to remove


### External Helpful Classes

FunctionSet


## ComboManager


### Class Description

Class tool that will manage combinations from a container. It handles stepping through all possible combinations, as well as branching with inclusions and exclusions.


### Similar Classes

std::next_permutation

std::previous_permutation


### Key Functions

constructor(container) - initializes and assigns the container from which combinations are generated

SetContainer(container) - Assign a container for the class to collect combinations from

MakeCombinations(number) - Returns a vector of all possible combinations of the items

CalculateCombinations(number) - Calculates the total number of possible combinations


### Error Conditions



1. The size of the requested combinations exceeds the size of the container - User Error, provide an exception stating that the size of the requested combinations is out of bounds


### Expected Challenges



* How best to return the combinations (in full list form or as a form of generator)

* How to handle the bounding for inclusions and exclusions.


### External Helpful Classes

IndexSet


## BruteForceOptimizer


### Class Description

Designed to systematically explore all (or many) possible combinations of a given set of items/inputs in order to maximize (or minimize) a specified value function.


### Similar Classes

std::next_permutation

std::previous_permutation


### Key Functions

SetItems(items) - Stores the item list in the optimizer.

Backtrack( index, currentScore, curentSelection, ...) - Recursively checks combinations and stops at predetermined limits

FindOptimalSolution() - The main driver that initiates the brute-force or backtracking search:

Returns the best score found and the corresponding item subset.


### Error Conditions



1. Invalid Value Function - Programmer Error (assert) if the user never sets a valid function before calling findOptimalSolution().
2. Empty Item Set –Could be a recoverable error (throw an exception or return (0, {}) indicating no items) if it’s actually permissible to have zero items. 
3. Value Function Errors - a combination of items fails to compute with the given value function - return exception stating value function failure


### Expected Challenges



* Complexity: Implementing backtracking in a clean, maintainable way can be tricky. Recursion pitfalls, debugging partial solutions, etc.
* Efficiency: Brute force can grow exponentially with item count. You might need bounding or pruning optimizations (like branch-and-bound, memoization in dynamic programming, etc.)


### External Helpful Classes

CSE Assert class

DataGrid class

Graph class

DataMap class


## MemoryFactory


### Class Description

A memory manager where collections of the same type are stored to be given out as requested.

When a new object of the factory type is created, the factory should provide the memory for it. When an object is deleted, the factory should reclaim the memory to be handed out again. When the number of objects the memory factory can store is reached, new memory should be allocated to accommodate additional objects.


### Similar Classes

std::allocator


### Key Functions

Default Constructor() - Constructor that allocates a set amount of the objects for later use

Constructor(amount) - Constructor that allocates the given amount of objects

Allocate() - Returns a pointer to one of the free pre-allocated objects

Deallocate(object pointer) - returns the used memory to the memory factory for later use

Destructor() - Frees all memory held by the factory

GetSpace() - Returns number of unused but allocated objects for this factory

ExpandSpace() - When the factory runs out of allocated memory, it reallocates the objects and generates more open object memory


### Error Conditions



1. The user attempts to create an object using the wrong MemoryFactory (i.e. they want an in from a string MemoryFactory) - User Error, returns an exception for them to correct their code
2. Bad_alloc - The MemoryFactory is unable to allocate the requested amount - Recoverable Error, either less memory needs to be allocated or you need to wait for freed space
3. User deletes the memory factory when they still need to use the memory allocated by that factory - User error, raise exception if any of the factory’s memory blocks are still in use


### Expected Challenges



* Memory leakage risks, which means finding a way to safely store a set amount of object blocks as well as keep them prepared when they are no longer being used
* Finding a secure way to either expand the number of reserved object blocks if the user reaches capacity or inform them that they have run out of objects
* Handling objects that were freed back to the MemoryFactory - they will need to be set in a way that does not give bad data to the user at a future point


### External Helpful Classes

CSE Assert

ReferenceVector