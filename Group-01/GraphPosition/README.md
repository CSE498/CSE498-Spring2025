# GraphPosition Class

## Description
This class aims to represent a position on the graph object. This will help in navigating graphs by providing a reference point. This is useful for implementing more complex graph algorithms. The main goal is to assist in iterating through the graph’s vertices and edges during a graph traversal, for example, and you can keep track of a specific “position” within the graph during an algorithm. 

## Similar Classes
- The std::vector class is one we should be familiar with as often times graphs are created using it. 
- The std:vector::iterator class would also likely assist in the traversal of a graph built using vectors. 
- The std::map class and it’s iterator would also be classes to be familiar with since they can also be used for graphs but also could be useful when managing vertices and edges of graphs. 
- Another class to be familiar with is std::optional since there may be times when a position might not exist in a graph due to that vertex not existing or an edge not connecting vertices.   

## Key Functions
- A constructor to initialize the position at a certain vertex. 
- A destructor for handling when graph traversal may be finished or a graph is destroyed. 
- A GetCurrentVertex function that could return the current vertex (position) in the graph that we are at. 
- A SetCurrentVertex function that could update the position we are currently at in the graph (advance to a new node). 
- An IsVisited and MarkVisited class to handle keeping track of vertices we’ve already traversed. 
- A GetNeighbors function to find what vertices the current vertex has edges to. 
- An AdvanceToNextNeighbor function that moves the position to the next adjacent vertex. 
- An IsValid function to test if a position is valid in the graph. 
- AddToPath and GetPath functions to handle keeping track and retrieval of the traversed path. 

## Error Conditions
- Accessing neighbors or graph positions with an uninitialized graph or using vertex ID’s that aren’t in the graph (Programmer Errors). 
- Attempting to move positions in the graph from a vertex with no neighbors or modifying the graph during the traversal which could make the state of the GraphPosition object invalid (User Errors). 

## Expected Challenges
- Understanding the best way to iterate through graphs efficiently that could potentially get very large. 
- Handling cases where the graph is modified while it’s being traversed could be difficult if that is something that’s allowed. 
- The best way to handle certain errors like invalid positions in the graph or deleted nodes in the graph. 
- Making sure to integrate with the graph class since it will likely depend on the graph class and vice versa may be difficult. 
- Keeping track of traversal paths and visiting vertices without taking up large amounts of memory. 
- Overall projects challenges will likely include having enough understanding of other groups projects to know when their classes could help to avoid duplication.  

## Other Class Projects
- The GraphPosition class is inherently dependent on the Graph class that we are also tasked with creating. 
- The DataMap class from group 2 could be useful for storing information if we want GraphPosition to track data like graph object weights or labels. 
- The StateGridPosition class from group 2 would also likely have a lot of similarities with the GraphPosition class. 
- The IndexSet class from group 4 could help when thinking about managing what nodes we’ve visited in certain traversals.  