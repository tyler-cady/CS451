#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Node {
    string state;  // State of the game.
    vector<int> path;  // Path taken
    int depth;  // Node depth
    Node* parent;  // Pointer to the parent node.
    float cost;  // Cost to reach this node.

    Node(string state, vector<int> path, int depth, Node* parent = nullptr, float cost = 0.0)
        : state(state), path(path), depth(depth), parent(parent), cost(cost) {}
};

// Check if the state is a goal state (counter is 0)
bool is_goal(Node* node) {
    return node->state.empty(); 
}

// Function to get piles from the state string
unordered_map<int, int> get_piles(const string& state, int& counter) {
    unordered_map<int, int> piles;  // Maps pile index to the card on top
    stringstream ss(state);
    ss >> counter;  // Read the counter

    string pile_data;
    while (ss >> pile_data) {
        int pile_index = pile_data[0] - '0';  // Convert char to int
        int card = pile_data[2] - '0';  // Assuming the card is after a space
        piles[pile_index] = card;  // Assign card to pile index
    }

    return piles;
}

// Expand the node to create successors based on Free Cell rules
vector<Node*> expand(Node* node) {
    vector<Node*> successors;
    int counter;
    auto piles = get_piles(node->state, counter);

    // Iterate through each pile to create successors
    for (const auto& pile : piles) {
        int pile_index = pile.first;
        int card = pile.second;

        // 1. Move to another pile if it's smaller
        for (const auto& target_pile : piles) {
            int target_index = target_pile.first;
            int target_card = target_pile.second;
            if (target_card < card) { 
                string new_state = node->state; 
                new_state += " " + to_string(target_index) + " " + to_string(card);  // Move card to target pile
                successors.push_back(new Node(new_state, node->path, node->depth + 1, node));
            }
        }

        int empty_pile_index = 3;  // Example index for empty pile
        if (piles.find(empty_pile_index) == piles.end()) {  // If the pile does not exist, it is empty
            string new_state = node->state;
            new_state += " " + to_string(empty_pile_index) + " " + to_string(card);  // Move card to empty pile
            successors.push_back(new Node(new_state, node->path, node->depth + 1, node));
        }
        if (card == counter) {
            string new_state = node->state;
            new_state.erase(new_state.find(to_string(card)));  // Remove the card from state (basic implementation)
            successors.push_back(new Node(new_state, node->path, node->depth + 1, node));
        }
    }

    return successors;
}

// A* algorithm implementation
Node* AStar(ofstream& nodes_log, function<float(Node*)> heuristic, const string& initial_state) {
    auto cmp = [heuristic](Node* a, Node* b) {
        return (a->cost + heuristic(a)) > (b->cost + heuristic(b));
    };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> fringe(cmp);

    Node* initial_node = new Node(initial_state, {}, 0); // Set the initial state
    fringe.push(initial_node);

    nodes_log << "Visiting Node: State: " << initial_node->state << "\n";

    while (!fringe.empty()) {
        Node* current = fringe.top();
        fringe.pop();

        if (is_goal(current)) {
            return current;
        }

        vector<Node*> successors = expand(current);
        for (Node* successor : successors) {
            successor->cost = current->cost + 1;
            fringe.push(successor);
            nodes_log << "Visiting Node: State: " << successor->state << "\n";
        }
    }

    return nullptr;
}

// Print solution
void print_solution(Node* goal_node, ofstream& out) {
    if (!goal_node) {
        out << "No solution found.\n";
        return;
    }

    out << "Solution found:\n";
    Node* current = goal_node;
    vector<int> path;
    while (current != nullptr) {
        path.insert(path.begin(), current->path.back());
        current = current->parent;
    }

    for (int idx : path) {
        out << "Step: " << idx << "\n";
    }      
}

// Test case function
void run_test_case(const string& initial_state, const string& log_file_name, const string& result_file_name, function<float(Node*)> heuristic) {
    ofstream a_star_log(log_file_name);
    Node* a_star_result = AStar(a_star_log, heuristic, initial_state);
    a_star_log.close();

    ofstream a_star_result_log(result_file_name);
    print_solution(a_star_result, a_star_result_log);
    a_star_result_log.close();
}

int main() {
    // Test cases
    string free_cell_1 = "10 3:4 2:5 1:1 2:2 3:6 4:7 5:10 6:9 7:3 8:8"; // Counter is 10, one pile with cards [4,5,1,2,6,7,10,9,3,8]
    string free_cell_2 = "12 1:2 2:11 3:4 1:3 2:12 3:6 1:1 2:7 3:8 3:9 3:10 4:5"; // Counter is 12 with specified piles

    auto heuristic1 = [](Node* node) {
        int counter;
        auto piles = get_piles(node->state, counter);
        int misplaced = 0;
        int blocked = 0;

        for (const auto& pile : piles) {
            int pi = pile.first; // pile index
            int card = pile.second;

            if (card != counter) misplaced++; 
            
            for (const auto& target_pile : piles) {
                if (target_pile.second > card) blocked++; 
            }
        } 
        return static_cast<float>(misplaced + blocked);
    };

    auto heuristic2 = [](Node* node) {
        int counter;
        auto piles = get_piles(node->state, counter);
        float weighted_misplacement = 0;
        int empty_piles = 0;
        int total_piles = piles.size();
        
        // Determine how many piles are empty
        for (const auto& pile : piles) {
            if (pile.second == 0) {
                empty_piles++;
            }
        }

        // Compute the weighted misplacement
        for (const auto& pile : piles) {
            int card = pile.second;

            // Ignore empty piles in the misplacement calculation
            if (card != 0) {
                // Difference between the top card and the current counter
                int difference = abs(card - counter);
                weighted_misplacement += difference;  // Greater difference -> higher penalty
            }
        }

        // Penalty for no empty piles
        float empty_pile_penalty = 0.0;
        if (empty_piles == 0) {
            empty_pile_penalty = 5.0;  // Increase this value to prioritize creating empty piles
        }

        // Heuristic is the sum of weighted misplacement and empty pile penalty
        return weighted_misplacement + empty_pile_penalty;
    };



    run_test_case(free_cell_1, "free_cell_1_log_heuristic1.txt", "free_cell_1_result_heuristic1.txt", heuristic1);
    run_test_case(free_cell_1, "free_cell_1_log_heuristic2.txt", "free_cell_1_result_heuristic2.txt", heuristic2);

    run_test_case(free_cell_2, "free_cell_2_log_heuristic1.txt", "free_cell_2_result_heuristic1.txt", heuristic1);
    run_test_case(free_cell_2, "free_cell_2_log_heuristic2.txt", "free_cell_2_result_heuristic2.txt", heuristic2);

    return 0;
}
