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

Node *Graph::find_closest_node(double lon, double lat) {
    double min_distance = 99999;
    Node* node_founded = nullptr;

    for (auto node: nodes) {
        double distance = std::sqrt(std::pow(node->lat - lat, 2) + std::pow(node->lon - lon, 2));
        if (distance < min_distance) {
            node_founded = node;
            min_distance = distance;
        }
    }

    return node_founded;
}


Node* Graph::find_node(double lon, double lat) {
    for (Node* node: nodes) {
        if (node->lon == lon && node->lat == lat) {
            return node;
        }
    }
    return nullptr;
}

Node* Graph::add_node(double lon, double lat) {
    auto new_node = new Node{lon, lat, {}};
    nodes.push_back(new_node);

    return new_node;
}

void Graph::add_edge(double lon, double lat, double lon_to, double lat_to, double distance) {
    Node* node1 = find_node(lon, lat);
    Node* node2 = find_node(lon_to, lat_to);

    if (!node1 || !node2)
        throw std::runtime_error("Not found nodes");

    node1->nodes.emplace_back(node2, distance);
    node2->nodes.emplace_back(node1, distance);
}

void Graph::add_edge(Node *node1, Node *node2, double distance) {
    node1->nodes.emplace_back(node2, distance);
    node2->nodes.emplace_back(node1, distance);
}

double Graph::bfs(Node *node1, Node *node2) {
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

double Graph::dfs(Node* node1, Node* node2) {
    std::unordered_set<Node*> visited;
    std::stack<std::pair<Node*, double>> stack;

    stack.push({node1, 0});
    visited.insert(node1);

    while (!stack.empty()) {
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

double Graph::dijkstra(Node *start, Node *end) {
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

double Graph::heuristic_dijkstra(Node *start, Node *end) {
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
