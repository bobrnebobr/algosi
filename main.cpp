#include <vector>
#include <chrono>
#include <iostream>

#include "utils.h"

typedef long long ll;

using namespace std;
using namespace chrono;

int main() {
    auto graph = parse_graph_from_file("../data/spb_graph.txt");

    auto my_node = graph.find_closest_node(30.502716,59.935475);
    auto end_node = graph.find_closest_node(30.338501,59.927334);


    auto start_time = high_resolution_clock::now();
    cout << graph.bfs(my_node, end_node) << std::endl;
    auto end_time = high_resolution_clock::now();
    auto duration = end_time - start_time;
    cout << "BFS: " << duration.count() << " microseconds"<< std::endl;

    start_time = high_resolution_clock::now();
    cout << graph.dfs(my_node, end_node) << std::endl;
    end_time = high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "DFS: " << duration.count() << " microseconds" << std::endl;

    start_time = high_resolution_clock::now();
    cout << graph.dijkstra(my_node, end_node) << std::endl;
    end_time = high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "DIJKSTRA: " << duration.count() << " microseconds" << std::endl;

    start_time = high_resolution_clock::now();
    cout << graph.heuristic_dijkstra(my_node, end_node) << std::endl;
    end_time = high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "HEURISTIC DIJKSTRA: " << duration.count() << " microseconds" << std::endl;
}