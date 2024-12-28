#include "utils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator ()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);  // Комбинирование хешей
    }
};

Graph parse_graph_from_file(const std::string& path_to_file) {
    // O(L * S + E), где L кол-во строк в файле, S - длина строки, E - кол-во рёбер
    Graph graph;
    std::ifstream file(path_to_file);
    std::unordered_map<std::pair<double, double>, Node*, PairHash> ready_nodes;

    if (!file.is_open()) {
        throw std::runtime_error("Something went wrong cannot open file " + path_to_file);
    }

    std::string line;
    int counter = 0;
    while (std::getline(file, line)) {
        std::cout << counter++ << "\n";
        std::istringstream stream(line);
        std::string coords, connections;

        if (!std::getline(stream, coords, ':') || !std::getline(stream, connections)) {
            throw std::runtime_error("invalid format");
        }

        double lon, lat;
        {
            std::istringstream coords_stream(coords);
            char sep;

            coords_stream >> lon >> sep >> lat;

            if (ready_nodes.find({lon, lat}) == ready_nodes.end()) {
                auto new_node = graph.add_node(lon, lat);
                ready_nodes[{lon, lat}] = new_node;
            }

        }

        std::istringstream edges_stream(connections);
        std::string connection;
        while (std::getline(edges_stream, connection, ';')) {
            std::istringstream edge_stream(connection);
            double lon_to, lat_to, distance;
            char sep;

            edge_stream >> lon_to >> sep >> lat_to >> sep >> distance;
            if (ready_nodes.find({lon_to, lat_to}) == ready_nodes.end()) {
                auto new_node = graph.add_node(lon_to, lat_to);
                ready_nodes[{lon_to, lat_to}] = new_node;
            }
            graph.add_edge(ready_nodes[{lon, lat}], ready_nodes[{lon_to, lat_to}], distance);
        }
    }

    file.close();
    return graph;
}