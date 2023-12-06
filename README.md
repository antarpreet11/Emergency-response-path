# Project description : 
Implementation of an Undirected Graph of vertices denoting locations and edges denoting paths having travel time as the weight. The objective was to find the fastest path to be taken by an ambulance given the traffic conditions.

# Operations :
**INSERT** to insert an edge between 2 given vertices  
**LOAD** to load a file full of INSERT commands  
**PRINT** to print all the edges of a given vertex  
**DELETE** to delete a vertex from the graph  
**PATH** to print the lowest weight path between 2 given vertices  
**LOWEST** to print the lowest weight between 2 given vertices  
**TRAFFIC** to update the variables d(distance), s(maxspeed) and A(adjustment factor) that account for the weight of an edge  
**UPDATE** to load a file full of TRAFFIC commands  

# Implementation :
The Graph uses an adjacencyList array of Linked Lists for tracking edges. This optimizes for space in case of a sparse graph.
To calculate the lowest path between 2 vertices and the weight of said path, **dijkstra's algorithm** was used.  
In order to have a worst case time complexity of **O(|E|log(|V|))** where E is the number of edges and V is the number of vertices (assuming the graph is connected), a **MinHeap** class was created.  

# Testing :
Extensive testing was done using **large** custom generated input files consisting of over 5000 lines. Memory leaks were tested using **Valgrind**.
