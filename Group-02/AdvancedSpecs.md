## <span id="group-2" style="color: blue">Group 2: Advanced Class Specification Document</span>

### DataMap

**Class Description:**

The DataMap advanced class shall utilize an std::unordered_multimap or std::unordered_map as the underlying data structure. The advanced class shall assign keys of std::string names and values of any possible value such as ints, doubles, std::string etc. The difference between the advanced version and the initial version is to allow functionality to have multiple values belonging to a single key. With this version, all of the methods developed for the initial version (such as insert, at, get etc) shall be changed accordingly to fit the new underlying data structure. Additionally, the DataMap shall contain its own memory management rather than utilizing std::any. This will be done by utilizing a base struct and a derived value struct. The goals for DataMap are to support all of the general map methods, ensure templated functionality for certain methods, support /revamping operators ([], ==, =, etc) and to “rewrite” existing functionality to better fit the application.

**Similar Classes:**

1. std::unordered_multimap (or std::unordered_map depending on implementation goals of application)
2. std::string
3. std::type_info

**Key Function:**

1. (not a function) struct BaseValue -> Abstract struct for type erasure of values
2. (not a function) struct Value : public BaseValue -> Derived from BaseValue to store type erased value 
3. (not a function) std::multimap<std::string, std::unique_ptr<BaseValue>> m_map
4. `template <typename T> void insert(const std::string& name, const T& val)` -> revamp insert method replacing std::any
5. `template <typename T> std::vector<T> at(const std::string& name) const` -> multimap shall return vector due to having multiple possible values
6. `bool contains (const std::string& name) const`
7. `void erase(const std::string& name)`
8. `void clear()`
9. `size_t size() const`
10. `bool empty() const`
11. `size_t count(const std::string& name)` -> with change to multimap need to count how many times key was inserted (length of vector)
12. `std::string to_string() const` -> returns a string of the value stored

**Error Conditions:**

Programmer error: Asserts will be added to all relevant methods to prevent errors such as type mismatch or clearing an already empty DataMap.

Potentially Recoverable error: The functionality in .at can be changed from using an assert to throwing an exception if the wrong type is specified from what the value actually is. 

User error: If the user attempts to access a key which does not exist, an assert could be implemented to catch this issue. However, this functionality has been implemented in a way that the user is not penalized as the key will be inserted with a default value within the map.

Tests will be written to ensure that both asserts and exceptions are properly invoked to ensure safe coding practices and shielding from errors.


**Expected Challenges:**

1. The new DataMap’s memory management must be carefully implemented (We plan on utilizing unique_ptrs).
2. Optimization for methods? Need to know when to utilize constexpr.
3. Will integrate lambdas if possible once we learn about the topic in class.
4. We would love to discuss with you the clear implementation that you are expecting out of this container. For instance, we could have the DataMap class just keep the essential functionality of a std::unordered_map rather than a multimap and prioritize the custom memory management instead of using std::any. Additionally, we would love for some guidance on the memory management part. For example, we took inspiration from your std::any implementation but if you had any other idea on how to implement this we would love to learn.

**Other Class Projects:**

Group 4: Audited string

Group 4: Assert

### StateGrid

**Class Description:**

This class will be used as a “map” of sorts for an agent to move around in, with several different types of states. Some will be walls, open spaces, the agents current position, a possible point to travel to another “floor”, and open spaces with enemies/other challenges. 

**Similar Classes:**

1. A DataMap would be needed to store states and their respective properties to index for agent movement and map information.  
2. We need to integrate with StateGridPosition using a Point struct, where StateGrid and SGP’s functions would coincide with each other and work together to keep track of the Agent’s position. 
3. Currently using an std::vector<std::string> for the m_grid variable, but our plan is to load in m_grid into an Audited Vector or Static Vector. 

**Key Function:**

1. `Constructor - StateGrid(std::string difficulty)`
2. `std::String get_state(int row, int col)` 
3. `void set_state(std::pair<int,int> new_position, std::pair<int,int> agent)`
4. `void displaygrid() )`
5. `Bool validate_position(std::pair<int,int> move)`
6. `std::vector<std::string>find_moves(int row, int col)`
7. `find_properties()` -> finds the properties of whatever the character/object is near/in. Ex. If the object is in water, it will sink. If it’s lava, it’ll sink and take damage, if next to a pushable object, etc. Currently we have a define_state() function, but with the addition of many new properties we need a more complex analysis that can call other functions
8. `load_map()` –> resource management to load in a map based on level/difficulty string(could be a parameter), probably coming from the constructor
9. `void set_conditions()` –> sets the attributes assigned to the object based on what is returned from find_properties
10. `void remove_conditions` –> similar to set_conditions, but this gets rid of the attributes set to the object when they should be removed based on if the object is far enough away from something else or enough time has passed, or state has changed 

**Error Conditions:**

User Error: The user could make a move that is invalid (move out of map, move into wall space, try to use item they don’t have) 

Programmer error: Could pass metadata into a FindMoves() or GetState() instead of position  

Programmer error: Need to make sure that maps auto generated or loaded in are valid in the context of the application 

Recoverable error: If the map to be loaded in cannot be located or is invalid, alert the user and default to a simple predetermined StateGrid 

Programmer error: Need to make sure to reset the map when calling load_map if whenever it should load a new instance. This includes positions, time passed, object attributes 

Programmer Error: Every possible move that can be made by the user must be validated either before presenting them their options or as the input a move, otherwise all organization related to the Grid will be skewed and could cause undefine behavior 

**Expected Challenges:**

1. StateGrid and StateGridPosition will obviously work very closely with each other, so communication between team members and how they change those classes will need to be consistent 
2. Now that we have discussed many more properties for the states in our grid, we will need an organized system to keep track of each state’s properties and how that affects the grid or the agent. 
3. Another possible idea is an auto-generating level map, which would be a complex task, and it must somehow be tested where it is still traversable and valid.
4. Now that we are integrating multiple project classes, there will need to be streamlined communication between them. We may need a Visitor.

**Other Class Projects:**

Group 1: Graph

Group 5: Datagrid

Group 7: DataFileManager 

Group 10: StaticVector  

Group 4: Assert for more informative and useful asserts 

**Main Additions from Initial Specs:**

1. Utilizing Audited Vector and DataMap within the StateGrid class for a more efficient and clean way to store the grid and the dictionary.
2. Either a resource management system to load in grids from a CSV file depending on the requested ‘difficulty’, or a way to possibly auto-generate valid grids on command.
3. Functions (find_properties()) that will analyze the states and their properties, and therefore make the correct actions to change the grid/agent when the state is traversed into. This could be made dynamic for cleanliness, because there will be several types of states with varying properties.
4. Functions (set/remove_conditions()) that can change the properties of a state, e.g. a pushable object being made static, or a previously dangerous state being made safe after a power up.

