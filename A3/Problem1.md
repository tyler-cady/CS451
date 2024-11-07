# Problem 1:

1. How many states are expanded for BFS in the worst case, in terms of n. 
- Theoretically this should be $n!$ because it is possible that, in the worst case, where all words could be connected to the initial word they all need to be expanded. 

2. How many states are stored in BFS in the worst case, in terms of n.
- The worst case all states are stored and expanded: O(n)

3. Is BFS complete for this problem?
- Yes. BFS will explore all the nodes.

4. Same as part A for DFS 
- DFS can also expand all possible states leading to n! expansions

5. Same as part B for DFS 
- Worst case all nodes are stored and expanded: O(n)
6. Same as part C for DFS
- DFS is complete as long as there are no cycles.
7. Same as part A for iterative deepening
- If iterative deepening explores up to the max depth it should be O(n * n!)
8. Same as part B for iterative deepening
-  Worst case is O(n)
9. Same as part c for iterative deepening
- Yes. Tt will eventually explore all possible paths and find a solution if one exists.
