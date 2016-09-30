#ifndef NODE_H
#define NODE_H


class node
{
public:
	node();
	~node();
	int bestNeighborCost(); // return the lowest cost from current node to the neighbor
	node * bestNeighbor();  // return the pointer of the lowest cost neightbor


	char weight;
	char isHighway;
	char index;
    float fN;//F=G+H
    float gN;
    float hN;
	int x;
	int y;
    node *parent;

	
};

#endif // NODE_H
