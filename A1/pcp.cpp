/* Post Correspondance Problem (PCP)*/
/**
 * Named after a guy named post not mail related 
 */

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;
using std::queue;
using std::stack;
using std::unordered_set;
using std::ofstream;

// Structure to represent a domino
struct Domino {
    string top; // Top string
    string bot; // Bottom string
};

// Structure to represent a Node in the search tree
struct Node {
    string top;      // Concatenated top string
    string bot;      // Concatenated bottom string
    vector<int> path; // Indices of dominoes used in the path
    int depth;       // Depth to track how many dominoes have been used
    Node* parent;    // Pointer to parent node

    Node(string top, string bot, vector<int> path, int depth, Node* parent = nullptr)
        : top(top), bot(bot), path(path), depth(depth), parent(parent) {}
};

// Function to expand a node and return its successors
vector<Node*> expand(Node* node, const vector<Domino>& dominoes) {
    vector<Node*> successors;

    // Loop over all dominoes to generate successors
    for (size_t i = 0; i < dominoes.size(); i++) {
        string new_top = node->top + dominoes[i].top;
        string new_bot = node->bot + dominoes[i].bot;
        vector<int> new_path = node->path;
        new_path.push_back(i); // Add current domino index to the path
        successors.push_back(new Node(new_top, new_bot, new_path, node->depth + 1, node));
    }

    return successors;
}

// Function to check if the goal is reached
bool is_goal(Node* node) {
    return node->top == node->bot;
}

// Breadth-First Search (BFS) for PCP with step limit
Node* BFS(const vector<Domino>& dominoes, int step_limit, ofstream& nodes_log) {
    // Initialize the fringe (queue) with the initial node (first domino)
    queue<Node*> fringe;
    Node* initial_node = new Node(dominoes[0].top, dominoes[0].bot, {0}, 1);
    fringe.push(initial_node);

    // Log the initial node
    nodes_log << "Visiting Node (BFS): Top: " << initial_node->top << " Bot: " << initial_node->bot << "\n";

    // Search loop
    while (!fringe.empty()) {
        Node* current = fringe.front();
        fringe.pop();

        // Check if we've reached the goal
        if (is_goal(current)) {
            return current;
        }

        // If step limit reached, don't expand further
        if (current->depth >= step_limit) {
            continue;
        }

        // Expand the current node and add its successors to the fringe
        vector<Node*> successors = expand(current, dominoes);
        for (Node* successor : successors) {
            fringe.push(successor);

            // Log the successor node
            nodes_log << "Visiting Node (BFS): Top: " << successor->top << " Bot: " << successor->bot << "\n";
        }
    }

    return nullptr; // Return nullptr if no solution is found within the step limit
}

// Depth-First Search (DFS) for PCP with step limit
Node* DFS(const vector<Domino>& dominoes, int step_limit, ofstream& nodes_log) {
    // Initialize the fringe (stack) with the initial node (first domino)
    stack<Node*> fringe;
    Node* initial_node = new Node(dominoes[0].top, dominoes[0].bot, {0}, 1);
    fringe.push(initial_node);

    // Log the initial node
    nodes_log << "Visiting Node (DFS): Top: " << initial_node->top << " Bot: " << initial_node->bot << "\n";

    // Search loop
    while (!fringe.empty()) {
        Node* current = fringe.top();
        fringe.pop();

        // Check if we've reached the goal
        if (is_goal(current)) {
            return current;
        }

        // If step limit reached, don't expand further
        if (current->depth >= step_limit) {
            continue;
        }

        // Expand the current node and add its successors to the stack
        vector<Node*> successors = expand(current, dominoes);
        for (Node* successor : successors) {
            fringe.push(successor);

            // Log the successor node
            nodes_log << "Visiting Node (DFS): Top: " << successor->top << " Bot: " << successor->bot << "\n";
        }
    }

    return nullptr; // Return nullptr if no solution is found within the step limit
}

// Function to print the solution path
void print_solution(Node* goal_node, const vector<Domino>& dominoes, ofstream& out) {
    if (!goal_node) {
        out << "No solution found.\n";
        return;
    }

    out << "Solution found:\n";
    Node* current = goal_node;
    vector<int> path;
    while (current != nullptr) {
        path.insert(path.begin(), current->path.back()); // Store the path in reverse
        current = current->parent;
    }

    // Print the domino sequence
    for (int idx : path) {
        out << "Domino (" << dominoes[idx].top << ", " << dominoes[idx].bot << ")\n";
    }
}

int main() {
    // Open output files
    ofstream out("pcp-out.txt");
    ofstream nodes_log("pcp-nodes.txt");

    // Define the test cases
    vector<Domino> dominoes1 = {
        {"MOM", "M"},    // Initial domino (MOM, M)
        {"O", "OMOMO"}   // (O, OMOMO)
    };

    vector<Domino> dominoes2 = {
        {"AA", "A"} // Initial domino (AA, A)
    };

    const int step_limit = 10;

    out << "Test Case 1 (BFS):\n";
    Node* result1 = BFS(dominoes1, step_limit, nodes_log);
    print_solution(result1, dominoes1, out);

    out << "\nTest Case 1 (DFS):\n";
    Node* result2 = DFS(dominoes1, step_limit, nodes_log);
    print_solution(result2, dominoes1, out);

    out << "\nTest Case 2 (BFS):\n";
    Node* result3 = BFS(dominoes2, step_limit, nodes_log);
    print_solution(result3, dominoes2, out);

    out << "\nTest Case 2 (DFS):\n";
    Node* result4 = DFS(dominoes2, step_limit, nodes_log);
    print_solution(result4, dominoes2, out);

    // Close the output files
    out.close();
    nodes_log.close();

    return 0;
}
