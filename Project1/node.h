#ifndef NODE_H
#define NODE_H


class node
{
public:
    node();
    ~node();
    int bestNeighborCost(); // return the lowest cost from current node to the neighbor
    node * bestNeighbor();  // return the pointer of the lowest cost neightbor

    int weight;
    char isHighway;
};

#endif // NODE_H