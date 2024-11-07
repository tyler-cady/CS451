# Problem 3 
Consider a one-dimensional maze problem, which is represented by a list
telling you that if you are in a given position, then there are two possible
positions you can move to.  Consider the maze:

[ (1 (3 5)) (2 (3 6)) (3 (2 4)) (4 (2 3)) (5 (3 8))
  (6 (7 9)) (7 (4 8)) (8 (7 10)) (9 (10 11)) (10 (5 7)) ]
This says that if you are at position 1, then you can go to position 3 or 5.
If you are in position 2, then you can go to position 3 or 6, etc.
Starting at position 1, the object is to get to position 8.  Each move has
a cost of 1.  So the path cost is the number of edges on that path.

A.  Show the order the nodes are expanded in BFS, and show the resulting
tree.  Assume that you do not revisit a state you have already seen.
If you have a choice which node to visit next, you should choose
the node with the smallest value (for all parts of this question).
Output:
```
Pathway: 3, 5

Position: 3
Pathway: 2, 4

Position: 5
Pathway: 3, 8

Position: 2
Pathway: 3, 6

Position: 4
Pathway: 2, 3

SUCCESS!!
Goal: 8, Position: 8
States Expanded: 6
Tree: 1 --> 3 --> 5 --> 2 --> 4 --> 8
```

B.  Show the order the nodes are expanded in DFS, and show the resulting tree.
Assume you never revisit a state on the same path.
```
Position: 1
Pathway: 3, 5

Position: 5
Pathway: 3, 8

SUCCESS!!
Goal: 8, Position: 8
States Expanded: 3
Tree: 1 --> 5 --> 8
```
C.  Show the order the nodes are expanded in Iterative Deepening Search.
Assume that you never revisit a node on the same path.
Iterative depth = 2

Output:
```
Position: 1
Pathway: 3, 5

Position: 5
Pathway: 3, 8

Position: 3
Pathway: 2, 4

Position: 4
Pathway: 2, 3

Position: 2
Pathway: 3, 6

SUCCESS!!
Goal: 8, Position: 8
States Expanded: 6
Tree: 1 --> 5 --> 3 --> 4 --> 2 --> 8
```
D.  You will notice that a move can at most move you 4 spaces closer to
the goal.  Give an admissible heuristic based on that fact.
Heuristic:
Count number multiples of 4 from goal
Less than 4, heuristic is 0

```
Position: 1
Pathway: 3, 5

Position: 5
Pathway: 3, 8

Position: 3
Pathway: 2, 4

Position: 4
Pathway: 2, 3

Position: 2
Pathway: 3, 6

SUCCESS!!
Goal: 8, Position: 8
States Expanded: 6
Tree: 1 --> 5 --> 3 --> 4 --> 2 --> 8
```

E.  Show the tree that would be constructed by the A* algorithm using the
heuristic in part D.  In this part the object is to get to position 11,
instead of position 8.  Label the tree with the f-value of each node.
Also list the order that the nodes are expanded.  Assume you never revisit
a node you have already seen.

Output:
```
Position: 1
Pathway: 3, 5

Position: 5
Pathway: 3, 8

Position: 3
Pathway: 2, 4

SUCCESS!!
Goal: 8, Position: 8
States Expanded: 4
Tree: 1, (f: 1) --> 5, (f: 2) --> 3, (f: 3) --> 8, (f: 3
```