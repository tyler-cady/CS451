#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <cmath>
using namespace std;

struct Car
{
    vector<pair<int, int>> positions; // Positions occupied by the car
    bool is_horizontal;               // Orientation of the car
};

struct Node
{
    vector<Car> cars; // Cars in the parking lot
    vector<int> path; // Path taken
    int depth;        // Node depth
    Node *parent;     // Pointer to the parent node.
    float cost;       // Cost to reach this node.

    Node(vector<Car> cars, vector<int> path, int depth, Node *parent = nullptr, float cost = 0.0)
        : cars(cars), path(path), depth(depth), parent(parent), cost(cost) {}
};

// Check if the state is a goal state (your car reaches the goal position)
bool is_goal(Node *node, const pair<int, int> &goal)
{
    for (const auto &pos : node->cars[0].positions)
    {
        if (pos == goal)
        {
            return true;
        }
    }
    return false;
}

// Expand the node to create successors based on parking lot rules
vector<Node *> expand(Node *node, int n)
{
    vector<Node *> successors;

    for (int i = 0; i < node->cars.size(); ++i)
    {
        Car car = node->cars[i];

        // Move forward
        if (car.is_horizontal)
        {
            if (car.positions.back().second + 1 < n &&
                find_if(node->cars.begin(), node->cars.end(), [&](const Car &other)
                        { return find(other.positions.begin(), other.positions.end(), make_pair(car.positions.back().first, car.positions.back().second + 1)) != other.positions.end(); }) == node->cars.end())
            {
                vector<Car> new_cars = node->cars;
                for (auto &pos : new_cars[i].positions)
                {
                    pos.second += 1; // Shift horizontally
                }
                vector<int> new_path = node->path;
                new_path.push_back(i); // Log the car's move
                successors.push_back(new Node(new_cars, new_path, node->depth + 1, node));
            }
        }
        else
        {
            if (car.positions.back().first + 1 < n &&
                find_if(node->cars.begin(), node->cars.end(), [&](const Car &other)
                        { return find(other.positions.begin(), other.positions.end(), make_pair(car.positions.back().first + 1, car.positions.back().second)) != other.positions.end(); }) == node->cars.end())
            {
                vector<Car> new_cars = node->cars;
                for (auto &pos : new_cars[i].positions)
                {
                    pos.first += 1; // Shift vertically
                }
                vector<int> new_path = node->path;
                new_path.push_back(i); // Log the car's move
                successors.push_back(new Node(new_cars, new_path, node->depth + 1, node));
            }
        }

        // Move backward
        if (car.is_horizontal)
        {
            if (car.positions.front().second - 1 >= 0 &&
                find_if(node->cars.begin(), node->cars.end(), [&](const Car &other)
                        { return find(other.positions.begin(), other.positions.end(), make_pair(car.positions.front().first, car.positions.front().second - 1)) != other.positions.end(); }) == node->cars.end())
            {
                vector<Car> new_cars = node->cars;
                for (auto &pos : new_cars[i].positions)
                {
                    pos.second -= 1; // Shift horizontally
                }
                vector<int> new_path = node->path;
                new_path.push_back(i); // Log the car's move
                successors.push_back(new Node(new_cars, new_path, node->depth + 1, node));
            }
        }
        else
        {
            if (car.positions.front().first - 1 >= 0 &&
                find_if(node->cars.begin(), node->cars.end(), [&](const Car &other)
                        { return find(other.positions.begin(), other.positions.end(), make_pair(car.positions.front().first - 1, car.positions.front().second)) != other.positions.end(); }) == node->cars.end())
            {
                vector<Car> new_cars = node->cars;
                for (auto &pos : new_cars[i].positions)
                {
                    pos.first -= 1; // Shift vertically
                }
                vector<int> new_path = node->path;
                new_path.push_back(i); // Log the car's move
                successors.push_back(new Node(new_cars, new_path, node->depth + 1, node));
            }
        }
    }

    return successors;
}

// Manhattan distance heuristic
float manhattan_distance(Node *node, const pair<int, int> &goal)
{
    int min_distance = INT_MAX;
    for (const auto &pos : node->cars[0].positions)
    {
        int distance = abs(pos.first - goal.first) + abs(pos.second - goal.second);
        min_distance = min(min_distance, distance);
    }
    return static_cast<float>(min_distance);
}

// Straight-line distance heuristic
float straight_line_distance(Node *node, const pair<int, int> &goal)
{
    int min_distance = INT_MAX;
    for (const auto &pos : node->cars[0].positions)
    {
        int distance = sqrt(pow(pos.first - goal.first, 2) + pow(pos.second - goal.second, 2));
        min_distance = min(min_distance, distance);
    }
    return static_cast<float>(min_distance);
}

// A* algorithm implementation
Node *AStar(ofstream &nodes_log, function<float(Node *)> heuristic, const vector<Car> &initial_cars, const pair<int, int> &goal, int n)
{
    auto cmp = [heuristic](Node *a, Node *b)
    {
        return (a->cost + heuristic(a)) > (b->cost + heuristic(b));
    };
    priority_queue<Node *, vector<Node *>, decltype(cmp)> fringe(cmp);

    Node *initial_node = new Node(initial_cars, {}, 0); // Set the initial state
    fringe.push(initial_node);

    nodes_log << "Visiting Node: State: ";
    for (const auto &car : initial_node->cars)
    {
        for (const auto &pos : car.positions)
        {
            nodes_log << "(" << pos.first << "," << pos.second << ") ";
        }
        nodes_log << (car.is_horizontal ? "H " : "V ");
    }
    nodes_log << "\n";

    while (!fringe.empty())
    {
        Node *current = fringe.top();
        fringe.pop();

        if (is_goal(current, goal))
        {
            return current;
        }

        vector<Node *> successors = expand(current, n);
        for (Node *successor : successors)
        {
            successor->cost = current->cost + 1;
            fringe.push(successor);
            nodes_log << "Visiting Node: State: ";
            for (const auto &car : successor->cars)
            {
                for (const auto &pos : car.positions)
                {
                    nodes_log << "(" << pos.first << "," << pos.second << ") ";
                }
                nodes_log << (car.is_horizontal ? "H " : "V ");
            }
            nodes_log << "\n";
        }
    }

    return nullptr;
}

// Print solution
void print_solution(Node *goal_node, ofstream &out)
{
    if (!goal_node)
    {
        out << "No solution found.\n";
        return;
    }

    out << "Solution found:\n";
    Node *current = goal_node;
    vector<int> path;
    while (current != nullptr && !current->path.empty())
    {
        path.insert(path.begin(), current->path.back());
        current = current->parent;
    }

    for (int idx : path)
    {
        out << "Step: " << idx << "\n";
    }
}

// Test case function
void run_test_case(const vector<Car> &initial_cars, const pair<int, int> &goal, int n, const string &log_file_name, const string &result_file_name, function<float(Node *)> heuristic)
{
    ofstream a_star_log(log_file_name);
    Node *a_star_result = AStar(a_star_log, heuristic, initial_cars, goal, n);
    a_star_log.close();

    ofstream a_star_result_log(result_file_name);
    print_solution(a_star_result, a_star_result_log);
    a_star_result_log.close();
}

int main()
{
    // Test cases
    vector<Car> parking_lot_1 = {
        {{{1, 2}, {2, 2}}, false}, // Your car
        {{{4, 5}, {5, 5}}, false},
        {{{4, 1}, {4, 2}, {4, 3}}, true},
        {{{2, 4}, {2, 5}}, true}};
    pair<int, int> goal_1 = {5, 2};

    // Run test case with Manhattan distance heuristic
    run_test_case(parking_lot_1, goal_1, 6, "parking_lot_1_manhattan_log.txt", "parking_lot_1_manhattan_result.txt",
                  [&](Node *node)
                  { return manhattan_distance(node, goal_1); });

    // Run test case with Straight-line distance heuristic
    run_test_case(parking_lot_1, goal_1, 6, "parking_lot_1_straight_line_log.txt", "parking_lot_1_straight_line_result.txt",
                  [&](Node *node)
                  { return straight_line_distance(node, goal_1); });

    return 0;
}
