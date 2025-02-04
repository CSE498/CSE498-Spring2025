## <span id="group-7" style="color: blue">Group 7: Euler</span>

**Members**: Anand Pinnamaneni, Bao Tran, Duong Tran, Siddhartha Bhattacharya, and Nathan Staniszewski

**Shared Interests**: Science

**Notable Strengths**: Algorithms, Math

### Classes to Build

| Class               | Description |
| ------------------- | ----------- |
| *Output Log* | A simple logging system for programmers to log events of their choice; often helpful for debugging. It may have multiple levels of output, perhaps "Silent", "Normal", "Verbose", and "Debug". Consider optional time-stamps on log. |
| *Audited Array*  | Functionality of [`std::array`](https://en.cppreference.com/w/cpp/container/array) (possibly called `cse::Array`) but when compiled in debug mode, checks every index attempt to ensure it is valid and in range; similar checks for iterators.  You can define you array as `template <typename T, size_t N> struct array;` as you begin to develop it.  Unfortunately you can not derive directly from `std::array` because that class is an "[aggregate type](https://en.cppreference.com/w/cpp/language/aggregate_initialization)", which, in part, means that it cannot be inherited and keep its properties.  |
| **`DataFileManager`** | A class to manage a data file where the user may want to periodically update its status.  When an `Update()` method is called, the manager should trigger a set of stored functions to build a new row in the fole; each result from the function calls should be placed in their own columns. |
| **`Scheduler`**     | Schedules a set of processes based on a "priority" measure and returns the ID of which one should go next. The priority of a process should be proportional to how often it is scheduled. This class can be built to be probabilistic or evenly integrated. |
| **`Serializer`**    | A tool to either SAVE or LOAD values from memory.  When `serializer.Serialize(x)` is called on value `x`, it should either save or load the value based on the current mode.  When stepping through code in "save: mode, it stores everything to a stream; in load mode it would step through the same set of function (with the same `Serialize` calls) going in the same order and pulls everything out from the stream to restore state. |

### Application Suggestion

An **ecology simulator**.  A user provides a set of species and how species interact.  For example, wolves eat rabbits, but have only a small chance of finding any given rabbit.  If there are a lot of rabbits, the wolves eat well, but if there are too few the wolves have trouble finding any.  This should create traditional predator-prey oscillations, as described by [Lotka-Volterra equations](https://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equations).  Note that you don't need to implement the equations directly, the system should produce them naturally.  While having two species is well understood, the math becomes far more complicated when you add in too many more, but natural ecologies have a huge number of species.

Suggested **challenges**: This is an obvious choice for a web app, and it would be fascinating to watch.  Connecting it in to natural studies to see if the results match would also be very useful.
