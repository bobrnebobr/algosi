#include <cmath>
#include <stdexcept>
#include <queue>
#include <limits>
#include <chrono>
#include <unordered_set>
#include <iostream>
#include <stack>
#include <unordered_map>
#include "Graph.h"

Node *Graph::find_closest_node(double lon, double lat) { // O(n) так как итерируемся по всем нодам, O(1) по памяти
    double min_distance = 99999;
    Node* node_founded = nullptr;

    for (auto node: nodes) { // O(n)
        double distance = std::sqrt(std::pow(node->lat - lat, 2) + std::pow(node->lon - lon, 2));
        if (distance < min_distance) {
            node_founded = node;
            min_distance = distance;
        }
    }

    return node_founded;
}


Node* Graph::find_node(double lon, double lat) { // o(n) так как итерируемся по всем вершинам, по памяти O(1)
    for (Node* node: nodes) { // O(n)
        if (node->lon == lon && node->lat == lat) {
            return node;
        }
    }
    return nullptr;
}

Node* Graph::add_node(double lon, double lat) { // O(1)
    auto new_node = new Node{lon, lat, {}};
    nodes.push_back(new_node);

    return new_node;
}

void Graph::add_edge(double lon, double lat, double lon_to, double lat_to, double distance) { // O(n), mem - O(1)
    Node* node1 = find_node(lon, lat); // O(n)
    Node* node2 = find_node(lon_to, lat_to); // O(n)

    if (!node1 || !node2)
        throw std::runtime_error("Not found nodes");

    node1->nodes.emplace_back(node2, distance); // O(1)
    node2->nodes.emplace_back(node1, distance); // O(1)
}

void Graph::add_edge(Node *node1, Node *node2, double distance) { // O(1)
    node1->nodes.emplace_back(node2, distance); // O(1)
    node2->nodes.emplace_back(node1, distance); // O(1)
}

double Graph::bfs(Node *node1, Node *node2) { // O(V + E), где V - количество вершин, E - количество рёбер, по памяти O(V)
    std::queue<std::pair<Node*, double>> queue;
    std::unordered_set<Node*> visited;

    queue.push({node1, 0});
    visited.insert(node1);

    while (!queue.empty()) {
        auto [current, current_distance] = queue.front();
        queue.pop();

        if (current == node2) {
            return current_distance;
        }

        for (const auto& [neighbor, weight]: current->nodes) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push({neighbor, current_distance + weight});
            }
        }
    }
    return -1;
}

double Graph::dfs(Node* node1, Node* node2) { // O(V + E), по памяти O(V)
    std::unordered_set<Node*> visited;
    std::stack<std::pair<Node*, double>> stack;

    stack.push({node1, 0});
    visited.insert(node1);

    while (!stack.empty()) { // O(V + E)
        auto [current, current_distance] = stack.top();
        stack.pop();

        if (current == node2) {
            return current_distance;
        }

        for (const auto& [neighbor, weight] : current->nodes) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                stack.push({neighbor, current_distance + weight});
            }
        }
    }

    return -1;
}

double Graph::dijkstra(Node *start, Node *end) { // O((V + E) log V), mem = O(V + E)
    std::unordered_map<Node*, double> distances;
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

    for (auto node: nodes) {
        distances[node] = std::numeric_limits<double>::infinity();
    }

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_distance, current_node] = pq.top();
        pq.pop();

        if (current_node == end)
            return current_distance;

        for (auto& [neighbor, distance]: current_node->nodes) {
            double new_distance = current_distance + distance;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }

    return -1;
}

double Graph::heuristic_dijkstra(Node *start, Node *end) { // O((V + E) log V), mem - O(V + E)
    // но используется подсчет эвристик для вычисения лучших следующих вершин таким образои работает быстрее
    std::unordered_map<Node*, double> distances;
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

    for (auto node: nodes) {
        distances[node] = std::numeric_limits<double>::infinity();
    }

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_distance, current_node] = pq.top();
        pq.pop();

        if (current_node == end)
            return distances[current_node];

        for (auto& [neighbor, distance]: current_node->nodes) {
            double lat_diff = neighbor->lat - end->lat;
            double lon_diff = neighbor->lon - end->lon;
            double heuristic = std::sqrt(lat_diff * lat_diff + lon_diff * lon_diff);

            double new_distance = distances[current_node] + distance;
            double priority = new_distance + heuristic;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({priority, neighbor});
            }
        }
    }

    return -1;
}
