/**
 * My free cell problem:  
 * The problem contains cards numbered 1 to n, one card for each number.
 * A state of the problem contains the following:
 * A counter n.
 * Several piles of cards, each pile contains 0 to n cards, with each card appearing exactly once.
 * The successor function will do one of the following things:
 * Take the block on top of some pile, and place it on top of another pile, such that it is placed directly on a smaller numbered block.
 * Take the block on top of some pile and place it on an empty pile.
 * Take the block on top of some pile and throw it away, assuming that the number on the block matches the counter, then decrement the counter.
 * The problem is solved when the counter is 0, equivalently when there are no blocks left. 
 * Any valid state could be an initial configuration.
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;


struct Node {
    vector <vector<int>> piles;
    int counter;
    int cost;
    string state;
};  

vector<Node*> expand(Node* node) {
    vector<Node*> successors;
    for (int i = 0; i < 3; i++) {
        string new_state = node->state + to_string(i);
        vector<int> new_path = node->path;
        new_path.push_back(i);
        successors.push_back(new Node(new_state, new_path, node->depth + 1, node));
    }
    return successors;
}


bool is_goal(Node* node){
    return node -> counter == 0; 
}

Node* AStar(ofstream& nodes_log, function<float(Node*)> heuristic) {
    auto cmp = [heuristic](Node* a, Node* b) {
        return (a->cost + heuristic(a)) > (b->cost + heuristic(b));
    };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> fringe(cmp);

    Node* initial_node = new Node("start", {}, 0);
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