#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

struct Node {
    string state;
    vector<int> path;
    int depth;
    Node* parent;
    float cost; 

    Node(string state, vector<int> path, int depth, Node* parent = nullptr, float cost = 0.0)
        : state(state), path(path), depth(depth), parent(parent), cost(cost) {}
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

bool is_goal(Node* node) {
    return node->state == "goal";
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

int main() {
    ofstream a_star_log("a_star_nodes_log.txt");
    auto heuristic = [](Node* node) {
        return static_cast<float>(node->state.length());
    };
    Node* a_star_result = AStar(a_star_log, heuristic);
    a_star_log.close();

    ofstream a_star_result_log("a_star_result.txt");
    print_solution(a_star_result, a_star_result_log);
    a_star_result_log.close();

    return 0;
}
