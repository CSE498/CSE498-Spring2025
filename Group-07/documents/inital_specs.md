# OutputLog:

**Description:**   
Logging system designed to help programmers debug and test the behavior of the application. (Including time-stamps on log)

**Similar Classes:**   
std::cout; std::ofstream; std::stringstream

**Key Functions:**

- setLevel: Sets the verbosity level for the logger  
- enableTimestamps: Enables or disables timestamps in log messages.  
- Log: Logs a message if the provided level is less than or equal to the verbosity level  
- getTimeStamp: return the current timestamp  
- writeToStream: Handles writing log messages to the appropriate outputs

**Error Conditions:**

- Invalid log level passed to setLevel  
- Log message exceeds size limit  
- Timestamp retrieval failure

**Expected challenges:**

- Handling multiple outputs: The class should allow logging to the console, a file, or both  
- Thread safety : If the logger is used in a multithreaded application, ensuring that log messages remain ordered and consistent will require synchronization mechanisms  
- Timestamp formatting : Learning to format timestamps efficiently

**Other class projects:**

- Group 5: CSVfile  
- Group 9: EventQueue

# AuditedArray

**Description:** Should have the same function as std::array in C++ and should be hot-swappable. The AuditedArray should work for generic types. Although all functionality of std:array is achieved by AuditedArray, when this class is compiled in debug mode, the array will check each of its indices and ensure that they are valid. Will also set default initialization for all elements of array.   
**Similar Classes:** array

**Key Functions:** 

- T at(size\_t pos)  
- reference operator\[size\_t pos\]  
- T front()  
- T back()  
- const T\* data()  
- bool isValidIndex(size\_t pos)  
- bool checkAllIndices()

**Error Conditions:** 

- OutOfBounds: if a user reads or writes outside of the array, a runtime error will be raised.

**Expected Challenges:** 

- Ensure correct array size and index tracking to avoid off-by-one errors.   
- Define behavior for negative indices.  
- Will learn about how std::array is actually implemented.

**Other Class Dependencies**

- Group 2: AuditedVector  
- Group 4: Audited String, Assert  
- Group 8: Audited Pointer

# DataFileManager

**Description:** Organizes and updates the given data files.

**Similar Classes:** 

- ofstream  
- ifstream  
- vector  
- list  
- function  
- algorithm

**Key Functions:**

- update: Calls a stored function, gathers the results, then appends a new row to the file.  
- addFunction  
- openFile and closeFile  
- clearFunctions  
- listFunctions

**Error Conditions:**

- Adding an invalid function  
- Failure to open or write to the file  
- Invalid input or output from the program

**Expected Challenges:**

- Error Handling  
- Concurrency  
- I/O Performance  
- Resource Management

**Other Class Projects:**

- Group 1: Graph  
- Group 5: CSVfile

# Scheduler

# **Description:** Priority queue to schedule processes to run based on how often each process is used.

**Similar Classes:**

- priority\_queue   
- deque   
- queue   
- sort 

**Key Functions:**

- Initialize/delete scheduler  
- Insert/delete processes  
- Update number of times a process has run  
- Determine scheduling order/frequency for processes  
- Return ‘highest priority’ process in the scheduler

**Error Conditions:**

- Scheduler is empty  
- Process dies before being selected by scheduler  
- Bad priority algorithm could make some processes in the scheduler never run

**Expected Challenges:**

- Finding/implementing an effective scheduling priority algorithm  
- Slow down as number of processes in scheduler increases  
- Keeping track of process status

**Other Class Projects:**

- Group 1: WeightedSet  
- Group 8: RandomAccessSet  
- Group 9: EventQueue, EventManager

# Serializer

**Description:**  
Saves or loads values from memory using streams

**Similar Classes:**

- stringstream  
- istream  
- ostream

**Key Functions:**

- Initialize/delete Serializer  
- Save value(s) to the serializer  
- Load value(s) from the serializer  
- Change serializer mode between save and load

**Error Conditions:**

- Serialize undefined/NULL values  
- Load from empty Serializer

**Expected Challenges:**

- Increasing stream size as values are added to serializer  
- Making Serializer type generic

**Other Class Projects:**

- Group 3: FunctionSet  
- Group 5: CSVFile

