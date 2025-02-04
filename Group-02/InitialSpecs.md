## <span id="group-2" style="color: blue">Group 2: Class Specification Document</span>

### DataMap

**Class Description:**

The Datamap class is a data structure with map functionality that can assign keys of std::string names to values of any type of data (for example int, double, etc) and store it within the data structure. Datamap allows the user to set data (key value pairs) within and grab the data with safe  checks. Datamap can either be inherited from a map data structure or assign a member variable to one to contain the values. A full implementation of this class would require a setter to allow in key value pairs, a getter to access the pairs, helper functions to see if a key value pair exists within datamap and a delete function to remove a key from the map. Safe checks such as exceptions and asserts shall be included to ensure that users and programmers are shielded from errors.

**Similar Classes:**

1. Datamap shall utilize an underlying data structure (preferably a map) such as std::map or std::unordered_map
2. Datamap can use std::any, which allows for any type to be held in a container reference: https://stackoverflow.com/questions/24702235/c-stdmap-holding-any-type-of-value
3. Datamap can use an iterator to check within the map for the get function
4. Datamap shall use std::string for string keys

**Key Function:**

1. `Template <typename T> void set(std::string name, T val)` -> User sets a key value pair and adds it to the datamap
2. `Template <typename T> T Get(std::string name)` -> User can access a key values pair from the datamap if it exists
3. `Bool keyContain(std::string name)` -> utilized within Get to see if key is within map
4. `void delKey(std::string name)` -> Delete a key from the map if needed

**Error Conditions:**

Programmer error: Get, Set, Contains, and delKey shall include asserts to for any invalid arguments passed in within these functions

User error: Invalid types specified within Get will invoke an assert when the user calls this function

Tests will be written to ensure that both asserts and exceptions are properly invoked to ensure safe coding practices and shielding from errors.

**Expected Challenges:**

1. Datamap can be utilized within Stategrid. Implementation details might vary depending on the development of Stategrid. Must communicate with teammates extensively.
2. Research on datamap led to a topic called dynamic inheritance which might prove useful in the development of this class rather than utilizing std::any. Could be useful.
3. Compile time vs runtime in the development of knowing what the type is for when get is invoked. Further depth in this topic would be helpful in implementation.

**Other Class Projects:**

Group 4: Audited string

Group 4: Assert

### StateGrid

**Class Description:**

This class will be used as a “map” of sorts for the agent to move around in, with several different types of states. Some will be walls, open spaces, the agent's current position, a possible point to travel to another “floor”, and open spaces with enemies/other challenges. 

**Similar Classes:**

1. StateGrid shall almost certainly need a 2D std::vector or array to represent the rows and columns of our map grid. 
2. StateGrid shall most likely need an std::pair or tuple to represent the agent’s current coordinates (x,y), which would also be needed in StateGridPosition
3. StateGrid shall need an std::map to store metadata about the different grid section states

**Key Function:**

1. `Constructor - StateGrid(int rows, int cols, std::string difficulty)`
2. `std::string GetState(int row, int col)` 
3. `void SetState(int row, int col)`
4. `void DisplayGrid()`
5. `Bool Validate(int row, int col)`
6. `std::string FindMoves(int row,int col)`

**Error Conditions:**

Programmer error: Could pass metadata into a FindMoves() or GetState() instead of position

User error: The user could make a move that is invalid (move out of map, move into wall space, try to use item they don’t have) 

**Expected Challenges:**

1. StateGrid and StateGridPosition will obviously work very closely with each other, so communication between team members and how they change those classes will need to be consistent 
2. Will need to research how other games have been done to brainstorm different functionalities we could include.
3. Building the map randomly may be difficult unless we have prebuilt labyrinths or a complicated Search algorithm

**Other Class Projects:**

Group 1: Graph

Group 5: Datagrid

### StateGridPosition

**Class Description:**

This class is fairly straightforward, with its main purpose being to track where our character/objects are within the associated object in the StateGrid. This could use some sort of relative point, or a common center for calculating position. It also needs to keep track of orientation. This could use a common direction as “North” and use a 360 degree tracker for the direction it is facing. It will need to constantly be updated because some characters/objects can move and turn while others aren’t.

**Similar Classes:**

1. std::map
2. std::vector
3. std::algorithm
4. array
5. std::iterator
6. std::numeric

**Key Function:**

1. `GetGridPosition` -> (gets the center or whatever common point is in the stategrid)
2. `SetPosition/GetPosition` -> (sets/gets the position of the object within the stategrid)
3. `SetOrientation` -> (sets the rotation of the object)
4. `CalculatePosition` -> (calculates the position of the object relative to another object’s position, or relative to the center of the grid. Could use an optional argument to determine which)

**Error Conditions:**

Programmer error: Get, Set, Contains, and delKey shall include asserts to for any invalid arguments passed in within these functions

Programmer error: The user attempts to go out of the valid areas/locations. This could also happen if a calculation is done wrong

Programmer error: The possibility of rotating the orientation past 359 degrees needs to be kept track of and reset if the rotation is set to larger than that. Obviously invalid function arguments are always a possibility, but more likely to happen would be getting the wrong object for the corresponding position. It could be dangerous because it would probably still function with just the output being different.

**Expected Challenges:**

1. This is essentially a class that has each object of it assigned to another class that is where the main stuff goes. This is mainly setting and getting numbers and doing calculations. The biggest issue anticipated would be the calculations being difficult.

**Other Class Projects:**

Group 1: Graph Position

Group 3: DataTracker

Group 5: DataGrid

### ActionMap

**Class Description:**

The class will represent a map of strings to any type of callable entities, such as functions, lambdas, or functors. This allows dynamic associations of user actions to string identifiers, making it useful in applications like event-driven interfaces, user command bindings, or custom event handlers.

The core functionality should include:  
  1. The ability to add callable objects (functions, lambdas, or functors) to a map, using a string key.
  2. Trigger the function associated with a given string key. 
  3. The functions can be of any signature, for example, int(), void(int), or std::string(std::string).

The class can inherit from std::map or std::unordered_map, it could directly leverage the underlying container for storage. However, it is necessary to override certain methods to ensure that it only accepts callable objects and provides correct behavior. 

If not inheriting then std::map or std::unordered_map could be internally used as a member variable and expose similar functionality (via delegation), without the complexities of inheritance. 

**Similar Classes:**

1. std::map / std::unordered_map: Both are used for key-value storage, with std::unordered_map generally offering better performance for lookups.
2. std::function: A template class that can store any callable type (function pointer, lambda, or functor), which is key for this class
3. std::string / std::wstring: For the string keys.

**Key Function:**

Element (function) access
1. `void insert(std::string name, std::function fun)` -> Adds a function (of any signature) associated with the specified string key.
2. `void trigger(std::string name, Args&&... args)` -> Triggers the function associated with the provided name, passing arguments to it. The function is called with the given arguments.
3. `std::function& at(std::string name)` -> Returns the function associated with the given name with bounds checking.
4. `std::function& operator[](std::string name)` -> Returns the function associated with the given name.

Modifiers
1. `void remove(std::string name)` ->  Removes the function associated with the given name from the map.

Lookup
1. `bool contains(std::string name)` ->  Returns whether a function exists for the given name.

**Error Conditions:**

Programmer error:
1. Invalid function signature: If the wrong type or type of callable is added this should raise an assertion or throw a std::invalid_argument.
2. Missing function: When calling trigger(name) for a non-existent key, an exception (e.g., std::out_of_range) can be thrown to signal the key is missing.
3. Duplicate function name: If a function is added with a name that already exists and you want it to overwrite, raise an exception (e.g., std::invalid_argument).

User error: 
1. Empty key: If insert or trigger is called with an empty string as a name, this should be handled gracefully (return a failure condition or throw an exception).
2. Incorrect arguments: If arguments passed to trigger do not match the function’s signature, we could raise an exception or return a special error condition.

Recoverable error:
1. Memory limits: Although rare but if a memory allocation fails (e.g., during function addition or map expansion), this could raise a std::bad_alloc.

**Expected Challenges:**

1. Type Erasure: Ensuring that std::function is used correctly to store any callable type, and handling the differences in function signatures. It is necessary to use the correct function signature when adding or triggering functions.
2. Handling arguments in trigger: Supporting flexible function signatures means we need to handle various argument types gracefully. It is necessary to ensure that argument types match the stored function signatures.
3. Error handling: Deciding if/how to handle different types of errors gracefully, such as when a function is missing, or a function signature mismatch occurs.

**Other Class Projects:**

None

### AuditedVector

**Class Description:**

The Audited Vector class, when in release mode, acts exactly the same as the Vector STD class. However, when it is in debug mode, it will become significantly less efficient but will check whether the index is in range or not and whether it is valid. It will also perform similar checks on iterators for the vector as well.

**Similar Classes:**

1. std::vector

**Key Function:**

The main bulk of the vector code will be derived from the STL vector class. To perform the checks, our initial thinking is to create a function to activate debug mode, separate functions to perform each check for iterators and indexes whether they are in range and valid. We will also need to override most main vector functions to ensure it functions correctly.

**Error Conditions:**

The main set of conditions we will be responsive to are ones related to checking the indices and iterators. When in debug mode and an iterator or index is found to be invalid or out of range, the class will throw an exception with a detailed message as to why the code is invalid. These main errors will be caused by the user, as they will be accessing the vector incorrectly.

**Expected Challenges:**

Some expected challenges we will face will be how we track the iterators and indexes while in debug mode. Another challenge will be making sure that the class has the same functionality and efficiency as the STL vector class when in release mode. To tackle these, we will need to review the STL vector class in depth to figure out how it works at a closer level. We will also need to review iterators more in depth so that we can make sure the iterators are valid and in range efficiently.

**Other Class Projects:**

Group 4: Audited string

Group 4: Assert

Group 7: Audited Array

Group 6: Error Manager
