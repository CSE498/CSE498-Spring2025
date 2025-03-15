# Advanced GraphPosition Class

## Description
We have chosen the GraphPosition class as one of our functions to develop further. This is because having the flexibility to efficiently traverse a graph and treat it like more of a dynamic object than a static object will be extrememly useful. We plan to enhance GraphPosition by supporting various traversal methods and also enabling it to be used as an iterator for use in loops.

## Reset Traversal
- Add functionality to reset the traversal so that the set of visited vertices is empty along with the traversal path.

## Operator++
- Enabling the GraphPosition object to be treated like an iterator using the operator++. This will be done by overloading the operator++ function and having different cases for different traversal modes.

## Enum Class TraversalMode
- Likely need to create something like a scoped enumeration for the traversal mode including options like DFS, BFS, Random, and Weighted traversals. Then also will need a member variable to track this.
- May also need to add an operator bool so it can be checked in loops like while(pos).

## Custom Traversal Implementation
- Need to modify the AdvanceToNextNeighbor function (and potentially create a few other functions to help with this) to support the different traversal modes. 
- A deque will likeley be needed (member variable) to assist with BFS.
- Potentially add support to track if the Graph object the GraphPosition is associated with has been modified (to reset traversal).

