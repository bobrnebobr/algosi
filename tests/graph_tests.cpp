#include <gtest/gtest.h>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>
#include <fstream>
#include "../Graph.h"
#include "../utils.h"

class GraphTest : public ::testing::Test {
protected:
    Graph graph;

    void SetUp() override {
        Node *node1 = graph.add_node(1.0, 2.0);
        Node *node2 = graph.add_node(3.0, 4.0);
        Node *node3 = graph.add_node(5.0, 6.0);
        Node *node4 = graph.add_node(7.0, 8.0);
        Node *node5 = graph.add_node(10.0, 11.0);

        graph.add_edge(node1, node2, 5.0);
        graph.add_edge(node2, node3, 2.0);
        graph.add_edge(node3, node4, 4.0);
        graph.add_edge(node1, node3, 10.0);
    }

    void TearDown() override {}
};

TEST_F(GraphTest, TestBFS) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(7.0, 8.0);

    double distance = graph.bfs(start, end);
    EXPECT_EQ(distance, 14.0);
}

TEST_F(GraphTest, TestBFSFalse) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(10.0, 11.0);

    double distance = graph.bfs(start, end);
    EXPECT_EQ(distance, -1);
}

TEST_F(GraphTest, TestDFS) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(7.0, 8.0);

    double distance = graph.dfs(start, end);
    EXPECT_EQ(distance, 14.0);
}

TEST_F(GraphTest, TestDFSFalse) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(10.0, 11.0);

    double distance = graph.dfs(start, end);
    EXPECT_EQ(distance, -1);
}

TEST_F(GraphTest, TestDijkstra) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(7.0, 8.0);

    double distance = graph.dijkstra(start, end);
    EXPECT_EQ(distance, 11.0);
}

TEST_F(GraphTest, TestHeuristicDijkstra) {
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(7.0, 8.0);

    double distance = graph.heuristic_dijkstra(start, end);
    EXPECT_EQ(distance, 11.0);
}

TEST(GraphParserTest, TestParseGraphFromFile) {
    std::string path = "test_graph.txt";
    std::ofstream file(path);

    file << "1.0,2.0:3.0,4.0,5.0\n3.0,4.0:5.0,6.0,7.0\n5.0,6.0:7.0,8.0,9.0";
    file.close();

    Graph graph = parse_graph_from_file(path);
    Node *start = graph.find_node(1.0, 2.0);
    Node *end = graph.find_node(7.0, 8.0);

    double distance = graph.bfs(start, end);
    EXPECT_EQ(distance, 21.0);
}

TEST_F(GraphTest, TestNodeAddition) {
    Node *newNode = graph.add_node(9.0, 10.0);
    EXPECT_NE(newNode, nullptr);
    EXPECT_EQ(graph.find_node(9.0, 10.0), newNode);
}

TEST_F(GraphTest, TestEdgeAddition) {
    Node *node1 = graph.find_node(1.0, 2.0);
    Node *node2 = graph.find_node(3.0, 4.0);
    graph.add_edge(node1, node2, 3.0);

    double distance = graph.dijkstra(node1, node2);
    EXPECT_EQ(distance, 3.0);
}
