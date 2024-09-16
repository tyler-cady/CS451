# Tour of the homework
- geo-nodes.txt and pcp-nodes show the path through the nodes 
- geo-out.txt and pcp-out.txt show the outputs from the programs
## Compilation targets
- `make geo`
- `make pcp`
# Geography Problem 
## State:
- The state is represented by the Node struct
- Node is: word_chain string , path vector , depth int,  and parent node pointer
## Initial State:
- Initial state is a node that has word chain of just the first word
- Path with a single element 
- depth = 1 
- parent = nullptr
## Goal Test:
- Goal test is have all the words been used 
## Successor Function:
- Identify last character of the last word in path
- Find all words that haven't been used and start with the last char.
- Create new nodes for each valid new word


# PCP Problem
## State: 
- The state is represented by the Node struct
- Node struct is made of top and bottom strings, path vector, and depth int.
## Initial State:
- The initial state is created by selecting the first domino
- path begins with the first domino index 
- depth is initialized to 1

## Goal test:
- Uses is_goal function
- checks if top == bottom

## Successor function:
- Appends each domino's top and bottom strings to the current Node's top and bot strings, respectively. 
- Creates new Node instances with these updated strings, adds the current domino index to the path, increments the depth, and sets the parent to the current Node.