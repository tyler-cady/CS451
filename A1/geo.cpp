#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::vector;
using std::queue;
using std::stack;
using std::unordered_map;
using std::unordered_set;
using std::ofstream;

// Structure to represent a word with first and last characters
struct Word {
    string place; // The actual word
    char first;   // First character of the word
    char last;    // Last character of the word
};

// Structure to represent a Node in the search tree
struct Node {
    string word_chain;    // Concatenated word chain
    vector<int> path;     // Indices of words used in the path
    int depth;            // Depth to track how many words have been used
    Node* parent;         // Pointer to parent node

    Node(string word_chain, vector<int> path, int depth, Node* parent = nullptr)
        : word_chain(word_chain), path(path), depth(depth), parent(parent) {}
};

// Function to expand a node and return its successors
vector<Node*> expand(Node* node, const vector<Word>& words) {
    vector<Node*> successors;
    int last_idx = node->path.back();
    char last_char = words[last_idx].last;

    // Loop over all words to generate successors if the first character matches the last character of the current word
    for (size_t i = 0; i < words.size(); i++) {
        // Ensure that the word hasn't already been used and the first letter matches the last letter
        if (std::find(node->path.begin(), node->path.end(), i) == node->path.end() && words[i].first == last_char) {
            string new_chain = node->word_chain + " -> " + words[i].place;
            vector<int> new_path = node->path;
            new_path.push_back(i); // Add current word index to the path
            successors.push_back(new Node(new_chain, new_path, node->depth + 1, node));
        }
    }

    return successors;
}

// Function to check if the goal is reached (all words used)
bool is_goal(Node* node, int total_words) {
    return node->path.size() == total_words;
}

// Function to log node information to a file
void log_node(Node* node, ofstream& file) {
    if (node) {
        file << "Visited Node:\n";
        file << "Word Chain: " << node->word_chain << "\n";
        file << "Path: ";
        for (int idx : node->path) {
            file << idx << " ";
        }
        file << "\nDepth: " << node->depth << "\n\n";
    }
}

// Breadth-First Search (BFS) for the geography problem
Node* BFS(const vector<Word>& words, ofstream& file) {
    // Initialize the fringe (queue) with the initial node (first word)
    queue<Node*> fringe;
    Node* initial_node = new Node(words[0].place, {0}, 1);
    fringe.push(initial_node);

    // Search loop
    while (!fringe.empty()) {
        Node* current = fringe.front();
        fringe.pop();

        // Log the current node
        log_node(current, file);

        // Check if we've reached the goal (used all words)
        if (is_goal(current, words.size())) {
            return current;
        }

        // Expand the current node and add its successors to the fringe
        vector<Node*> successors = expand(current, words);
        for (Node* successor : successors) {
            fringe.push(successor);
        }
    }

    return nullptr; // Return nullptr if no solution is found
}

// Depth-First Search (DFS) for the geography problem
Node* DFS(const vector<Word>& words, ofstream& file) {
    // Initialize the fringe (stack) with the initial node (first word)
    stack<Node*> fringe;
    Node* initial_node = new Node(words[0].place, {0}, 1);
    fringe.push(initial_node);

    // Search loop
    while (!fringe.empty()) {
        Node* current = fringe.top();
        fringe.pop();

        // Log the current node
        log_node(current, file);

        // Check if we've reached the goal (used all words)
        if (is_goal(current, words.size())) {
            return current;
        }

        // Expand the current node and add its successors to the stack
        vector<Node*> successors = expand(current, words);
        for (Node* successor : successors) {
            fringe.push(successor);
        }
    }

    return nullptr; // Return nullptr if no solution is found
}

// Function to print the solution path to a file
void print_solution(Node* goal_node, const vector<Word>& words, ofstream& file) {
    if (!goal_node) {
        file << "No solution found.\n";
        return;
    }

    file << "Solution found:\n";
    Node* current = goal_node;
    vector<int> path;
    while (current != nullptr) {
        path.insert(path.begin(), current->path.back()); // Store the path in reverse
        current = current->parent;
    }

    // Print the word sequence
    for (int idx : path) {
        file << words[idx].place << " ";
    }
    file << "\n";
}

int main() {
    // Open file streams
    std::ofstream node_file("geo-nodes.txt");
    std::ofstream solution_file("geo-out.txt");

    // Test case 1
    vector<Word> words1 = {
        {"ABC", 'A', 'C'},
        {"CDE", 'C', 'E'},
        {"CFG", 'C', 'G'},
        {"EHE", 'E', 'E'},
        {"EIJ", 'E', 'J'},
        {"GHK", 'G', 'K'},
        {"GLC", 'G', 'C'}
    };

    // Test case 2
    vector<Word> words2 = {
        {"ABC", 'A', 'C'},
        {"CDE", 'C', 'E'},
        {"CFG", 'C', 'G'},
        {"EHI", 'E', 'I'},
        {"GJC", 'G', 'C'},
        {"GKG", 'G', 'G'}
    };

    solution_file << "Test Case 1 (BFS):\n";
    Node* result1 = BFS(words1, node_file);
    print_solution(result1, words1, solution_file);

    solution_file << "\nTest Case 1 (DFS):\n";
    Node* result2 = DFS(words1, node_file);
    print_solution(result2, words1, solution_file);

    solution_file << "\nTest Case 2 (BFS):\n";
    Node* result3 = BFS(words2, node_file);
    print_solution(result3, words2, solution_file);

    solution_file << "\nTest Case 2 (DFS):\n";
    Node* result4 = DFS(words2, node_file);
    print_solution(result4, words2, solution_file);

    // Close file streams
    node_file.close();
    solution_file.close();

    return 0;
}
