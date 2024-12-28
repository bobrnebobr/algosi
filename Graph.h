#ifndef POLYGON_GRAPH_H
#define POLYGON_GRAPH_H

#include "Node.h"
#include <unordered_set>


class Graph {
private:
    std::vector<Node*> nodes;
    double dfs_recursion(Node* current, Node* end, std::unordered_set<Node*>& visited, double distance=0.0);
public:
    Node* find_closest_node(double lon, double lat);
    Node* find_node(double lon, double lat);
    Node* add_node(double lon, double lat);
    void add_edge(double lon, double lat, double lon_to, double lat_to, double distance);
    void add_edge(Node* node1, Node* node2, double distance);

    double bfs(Node* node1, Node* node2);
    double dfs(Node* node1, Node* node2);
    double dijkstra(Node* start, Node* end);
    double heuristic_dijkstra(Node* start, Node* end);
};

#endif //POLYGON_GRAPH_H
