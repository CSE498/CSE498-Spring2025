# WeightedSet Class

## Description
A class that is a data structure similar to std::set, but each element is associated with a numerical “weight.” The total weight of all elements define a range, and elements can be efficiently accessed by indexing into this range. Indexing with a value between 0.0 and the total weight returns the corresponding element based on its cumulative weight.

## Similar Classes
- std::set
- std::map, std::unordered_map 
- std::vector
- std::accumulate (calculating total weight)

## Key Functions
- An insert and delete function to add and remove items from the WeightedSet. 
- A get function to get a specific item and a get_random function for a random index in a certain range.

## Error Conditions
- Inserting an item with a negative weight. 
- Accessing an index out of range or the weight of an item that doesn’t exist 
- Attempting to use any functions while the WeightedSet is empty.

## Expected Challenges
- Figuring out how to efficiently manage the WeightedSet so it can be indexed quickly even at a large size. 
- Learning about implementing random and certain algorithms for range queries and cumulative weight management. 

## Other Class Projects
- The Random class could be used for the random indexing of the WeightedSet. 
- The IndexSet class from Group 4 could potentially be used to hold the indices for the associated weights.