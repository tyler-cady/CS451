# Problem 2: Assuming n dominoes
PCP Problem:  You have a set of dominoes.  Each one
contains a string on the top and a string on the bottom.
The problem is to find a sequence of dominoes 
such that the concatenation of the strings on the top
gives the same string as the concatenation of all the 
strings on the bottom.  Dominoes may be used as many
times as you want.  Assume that the first domino is there.
Answer Parts A-I for PCP, assuming n dominoes.

1. How many states are expanded for BFS in the worst case, in terms of n. 
- Since there are n dominoes the number of possible sequences of length k is $n^k$
2. How many states are stored in BFS in the worst case, in terms of n.
- Stores up to $n^k$ states.
3. Is BFS complete for this problem?
- BFS is complete because it explores all possible sequences and BFS will eventually find a solution
4. Same as part A for DFS 
- In the worst possible case DFS could expand an infinite amount of states in its worst case.
5. Same as part B for DFS
- The number of states is proportional to the depth of the current path which is unbounded. As such it is also potentially infinite. 
6. Same as part C for DFS 
- DFS is not complete for this problem. DFS can potentially explore paths of infinite length.
7. Same as part A for iterative deepening
- Because iterative deepening can increase the depth limit, it is potentially infinite.
8. Same as part B for iterative deepening
- Because it again is proportional the size is potentially unbounded. 
9. Same as part c for iterative deepening
- Yes. Iterative deepening avoids the DFS pitfalls by not traveling to infinite depth. 