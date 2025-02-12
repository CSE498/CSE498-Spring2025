Write Up \- Group 4

1\) A **class description**, including what its goals are, and what its high-level functionality should look like. This does not need to perfectly match the description you were given, but it should be in the same general spirit unless you confirm any changes with the instructors ahead of time.

2\) A list of **similar classes** in the standard library that you should be familiar with or use to inform the functionality you will be developing.

3\) A list of **key functions** that you plan to implement. This does not need to be an exhaustive list, but it should give a strong indication of how the class should be used.

4\) A set of **error conditions** that you will be responsive to. For each, indicate if it’s source was (1) *programmer error*, such as invalid arguments to a function, which should be caught by an assert, (2) a potentially *recoverable error*, such as a resource limitation, which should trigger an exception, or (3) a *user error*, such as invalid input, which needs to simply return a special condition for the programmer to respond to (note: these can usually be handled with exceptions as well if you prefer.)

5\) Any **expected challenges** that you will be facing, especially any extra topics you need to learn about. This information will help me make sure to cover topics early in the course or else provide your group with extra guidance on the project.

6\) A list of any **other class projects** from other groups that you think you may want to use, either in the development of your own classes or in your final application.

Feel free to use the table of contents on the left to navigate if viewing on G Docs.

# Class Descriptions

## BitVector

The goal of cse::BitVector is to store an array of bits such that bit operations can be performed between two BitVectors while allowing dynamic allocation of the array as it grows. Should be able to use any bit operator built into C++ and handle automatic allocation and deallocation much like an std::vector does.

## IndexSet

The goal of cse::IndexSet is to efficiently store and recall ranges of numbers that are in the set. IndexSet will dynamically allocate memory automatically, much like std::vector does. WIll pick an optimal storage strategy based on usage and/or hints from the programmer.

## Audited String

The goal of cse::String (aka Audited String) is to build off of std::string with extra debug mode functionality without impeding the production release. When debug mode is active, cse::String will check for bounds, character set validity, iterator validity, etc. More public classes may be needed to represent specific types of strings. When debug mode is inactive (e.g. releases) these checks are turned off for performance.

## RichText

The goal of cse::RichText is to represent formatted text in such a way that it can be created from and to other rich text formats such as HTML, Latex, Markdown, RTF, or ANSI. Formatting features that cse::RichText will support include, but are not limited to, bold, italic, underline, strikethrough, multilevel header, formatting escaping characters, monospace code quotes, block quotes, emoji, unicode, superscript and many more.

## Assert

The goal of cse\_assert is similar to assert in assert.h in that the code asserts that some value is true. In addition cse\_assert will support functionality to write custom messages to the error stream along with the filename and line number. This will enable easier debugging. Additionally, multiple different assert macros will be available for different use-cases, such as checking if two expressions are equal, or asserting that a location in code should never be reached.

# Similar Classes

## BitVector

* std::bitset  
  * Our class is the dynamically automatically allocating version of this class. It should support similar operations and intuition as this class.  
* std::vector  
  * Our class is essentially a std::vector\<bool\>. std::vector actually has a specific implementation for the boolean type, but we will be making a non-generic version that implements boolean specific functions.

## IndexSet

* std::span

  * We could integrate `std::span` with `IndexSet`. Something like:  
    `template <typename T> ConstructSpan(T *container, std::size_t idx)`

* std::vector, std::set

  * Like these std containers, cse::IndexSet will dynamically allocate memory as the set grows. Unlike the std, cse::IndexSet will pick an optimal storage strategy during runtime.

* cse::BitVector

  * A BitVector may be useful for storage if the elements stored in the set are scattered

## Audited String

* std::string  
  * This is the object that will be automatically audited during debugging sessions.  
* std::basic\_string  
  * A string that supports specific character types, an advanced version would work with this as well.

## RichText

* std::string  
  * The C++ std::string is too basic to support rich text, but will still be pivotal to representing text in a computer.  
* Audited String  
  * Can be used for debugging our class.  
* std::basic\_string  
  * cse::RichText will need support for character traits & character sets and this is the std implementation that supports them  
* cse::IndexSet  
  * A cse::IndexSet can efficiently store bursts of ranges, which many formatting consists of. May be useful to store some formatting information.  
* std \<format\>  
  * This text formatting library is primarily used in conjunction with printing formatted text to the terminal, but is the std way to store and format text.  
* Julia’s [styled strings](https://docs.julialang.org/en/v1/stdlib/StyledStrings/)  
  * We could use this for inspiration for creating RichText objects in C++ code

## Assert

* assert from std \<assert.h\>  
  * Our cse\_assert() should have all features from assert and more  
* assert from std \<cassert\> from C++26  
  * This assert due for C++26 has many of the features that we’re trying to implement  
  * [https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2264r7.html](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2264r7.html)  
* Rust’s [assert\_eq](https://doc.rust-lang.org/std/macro.assert_eq.html), assert\_ne macros  
  * On failure, these macros can print the values of the lhs and rhs to explain why they aren’t equal, instead of just reporting that the condition failed

# 

# Key Functions

## BitVector

* Boolean operations &, |, ^, \==, etc \[i.e BitVector& operator&=(const BitVector&)\]  
  * BitVector should implement all the boolean operators that std::bitset does.  
* bool operator==(const BitVector&) const \- equality checks  
* Dynamic allocation on the heap  
* Set bits (including those “out of range”) \- void set(size\_t index, bool value \= true)  
  * Set a bit anywhere in the array, dynamically allocating space automatically if needed.  
* Retrieve bits \- bool get(size\_t index) const  
* size\_t size() const: returns how many bits allocated  
* Efficient  
  * Some architectures have specific instructions for some of these operations

## IndexSet

* Dynamic allocation on the heap  
* void insert(size\_t index) \- add an index to set  
* void remove(size\_t index) \- remove index from set (if there)  
* bool contains(size\_t index) const \- check if index in set  
* size\_t size() const: number of indexes in set  
* std::vector \<size\_t\> getAllIndices() const \- enumerate entire set  
* std::optional\<std::pair\<size\_t, size\_t\>\> getNextRange(size\_t index) \- returns the next range from the index.  If the index is within a range, it returns the range following the one containing the index  
* std::optional\<std::pair\<size\_t, size\_t\>\> getPrevRange(size\_t index) \- returns the previous range from the index.  If the index is within a range, it returns the range preceding the one containing the index  
* std::optional\<std::pair\<size\_t, size\_t\>\> getContainingRange(size\_t index) \- returns the range containing this index if it exists within the set  
* iterator begin() \- an iterator to the start of the index set  
* iterator end() \- an iterator one past the end of the index set  
* iterator rbegin() \- a backwards iterator pointing at the end of the index set   
* iterator rend() \- a backwards iterator pointing one before the start of the index set  
* Picks a storage strategy  
  * Is expected to handle bursts of consecutive indexes, but it’s not guaranteed  
* Insert and remove  
* Efficient lookup

## Audited String

* Does not alter anything for release builds  
* Stand in for std::string during debug mode  
* Checks for errors such as range errors, character type errors, etc  
* Prints detailed debug information

## RichText

* Stores formatted rich text  
* Easy to implement a parser for  
* Converts to rich text formats  
* Performs analysis to determine whether the store text can be represented perfectly in a format, and if not, why.  
* Formats text for terminal output, so you can write `RichText` objects directly to `std::cout`

## Assert

* Does not alter anything for release builds  
* Includes all the functionality of std’s assert.h  
* Works in C++20 and up  
* Provides assert, assert equal, assert not equal, and assert never macros  
* Can provide message explaining what the assert is for

# 

# Error conditions

## Debug classes

Classes such as Audited String and Assert both have specialized uses for debugging. If a violation of a property occurs, the audits and asserts will bring the program to a halt and document the error in the output.

A release build will not have these modifications and as such the classes won’t be able to throw errors upon a violation.

## Runtime classes

The other classes BitVector, IndexSet, and RichText all return expected, variant, or custom struct results that are able to express any recoverable errors that occurred. Unrecoverable errors will throw an exception alongside a helpful error message.

### BitVector

Assuming BitVector has similar (or same) functionality as bitset

* `operator[]`  
  * If the index of the bit is out of range, this will throw an exception in debug mode, but is undefined behaviour in release mode  
* `test`, `set,` `reset`, `flip`  
  * Throws `std::out_of_range` if the index is not in range  
* Binary `AND`, `OR,` `XOR`, `NOT`  
  * `BitVector` will assume that if one vector is longer than the other, the “high” bits not included in the shorter vector will be assumed as zero.  

### IndexSet

* `getNextRange, getPrevRange, getContainingRange`  
  * Range may not exist, return an empty optional if that is the case

### RichText

* Convert from text should throw an exception when the input is malformed, or unable to be parsed in the format requested   
* Convert to text should have two modes:  
  * Strict mode \- throw an exception if the output format does not support some of the formatting in the text  
  * Loose mode \- output warnings (to a stream?) but return translated text regardless, dropping formatting if it is not supported by the output format  
    * Set a flag that can be checked?  
    * Maybe a tuple with the success as one value and the text as another

# 

# Expected Challenges

## BitVector

* We may need to consider endianness  
* We will need to determine which internal layout makes more sense (do we prioritize memory usage by bit packing at the cost of CPU, or should we store each bit in `BitVector` as a byte internally?)  
* There may be performance penalties of using `BitVector` compared to `std::vector<char>` or `std::vector<bool>`, and if so we should attempt to mitigate this  
* We will have to worry about thread-safety \- depending on how we implement this (either lock-based or not) will pose subsequent challenges.  
* Operator overloading issues should be considered, such as avoiding code duplication

## IndexSet

* We will need to determine what internal representation makes the most sense. If we design `IndexSet` for the express purpose of implementing `RichText`, we should store ranges of indices. However, a more general purpose implementation might benefit from marking each index individually using a `BitVector`.  
* Merging range issues might come up if a series of consecutive indices being merged into continuous range  
* Will need to consider how to manage scalability  
* Need to figure out what type to return in the iterator, either loop through all indices or through all ranges as pairs of numbers (one possibility is to provide both options, a user of the class could choose to use getAllIndicies)

## Audited String

* API will need to be designed in a way that makes an easy drop-in replacement for `std::string`  
* Will need to verify that we aren’t incurring performance penalties at run-time  
* Will need a way to detect iterators once invalid

## RichText

* We will need to determine some generic way to store formatting information  
* Need to handle the case where multiple styles overlap \- some may be compatible (ex. underline and color), but some are incompatible (color and another color)  
* Will need a way to handle styling conflicts  
* If we add some kind of stream support we will need a way to figure out whether it supports formatting (like colors), and if so, how it expects them to be output (escape char, api call, etc)  
* Formatters themselves will likely be complex and require their own separate classes

# Assert

* Macros can be inflexible, so we may want to move the core logic into a true C++ function  
* Macro arguments might be split unintentionally due to preprocessor argument pre-scanning  
* We can mitigate the above using `__VA_ARGS__`, but this doesn’t work if we also want the user to be able to provide a message. There may be other workarounds for this.  
* Need to make sure that cse\_assert works identically across all compilers, due to the fact that `__FILE__`, `__LINE__`, or `__func___` may work differently based on the compiler.

# 

# Other Relevant Class Projects

Group 1 Graph & Graph Position

	Although unlikely, if RichText needs to modify its text often, using a graph can be part of a solution to make it more efficient, however it’s probably overkill.

Group 2 DataMap

	RichText will need to have a map of formatting options to text on which it is applied. While DataMap may do this, it is most likely overkill vs a simple vector.

Group 3 FixedPoint

	Some formatting options might need to have accurate decimals

Group 3 DataTracker

	RichText needs to understand which formatting options were ignored, perhaps a DataTracker might be able to keep track of which formatting options were not accessed.

Group 5 Datum

	Formatting metadata might be text or a number, using this class could distinguish between the two.

Group 5 CSVfile

	One of the RichText Parsers could be a csv parser that stores all the data stored in RichText

Group 6 StaticString

	RichText might not need to allocate more space than is needed the first time, using a StaticString could improve performance.

Group 8 DynamicString

	If RichText does need a lot of operations or changes, then using a DynamicString can greatly enhance the speed by evaluating string operations more lazily.

Group 9 TextBox

	Our data structure is ideal for this use case, we should cater to this class.

Group 10 StaticVector

	Depending on the use case, if formatting options don’t need to grow, then using ~~an array~~  a StaticVector might be faster.