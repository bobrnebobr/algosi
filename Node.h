#ifndef POLYGON_NODE_H
#define POLYGON_NODE_H

#include <vector>


struct Node {
    double lon, lat;
    std::vector<std::pair<Node*, double>> nodes;
};


#endif //POLYGON_NODE_H
