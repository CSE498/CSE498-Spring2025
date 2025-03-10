### **Group 07 Advanced Classes Proposal**

Duong Tran, Anand Pinnamaneni, Nathan Staniszewski, Bao Tran, Siddhartha Bhattacharya

### **Scheduler**

Currently

* Add/Remove process IDs  
* Get next ID  
* Scheduling based on process invocation count

Proposal

* Allow for each process to be given a ‘weight’ to its priority value  
  * Enables users to give higher/lower priority to different processes  
  * Initialize the scheduler with a probability vector as weight multipliers for each attribute.  
  * Each process has an associated vector with varying attribute values for scheduling.  
* Allow overriding of Scheduling order to bring a process to the front of the schedule

**Added/Modified Functions:**

- Add function to configure attribute weights  
- Add priority value weights  
- Add function to modify process attributes  
- Add function to move a process to the front of the scheduler’s queue  
- Add function to get attribute/probability vector for given process id

**Error Conditions:**

- Process attribute vector is incorrect length \-\> invalid argument exception  
- Overriding scheduling order for process not in the Scheduler  
- Adding a process that already exists \-\> raise invalid argument

**Expected challenges:**

- Tracking overridden processes in the Scheduler to avoid error conditions

### **Serializer**

Currently

* Save contents to a file with given file name (with basic types and containers)  
* Load contents from a file with given file name (with basic types and containers)  
* Changing mode of Serializer (from Load to Save and vice-versa)

Next

* Upgrade the Serializer so that they can handle more complicated thing  
  * Allow users to work with their own structs/classes  
  * Allow users to operate with complicated data structures (such as vector\<vector\<int\>\>  
  * The loader for those complicated class will be multiple files

**Added/Modified Functions:**

- Modify most of serialize() to recursively serialize (for nested vects, for example).  
- Checker for if the class for which serialize was invoked has a serialize() method  
- Possibly: serialize arbitrary external classes

**Error Conditions:**

- Raise invalid argument if we call serialize using a class which does not have a serialize method

**Expected challenges:**

- Expanding this to serialize external classes (without requiring serialize method)

