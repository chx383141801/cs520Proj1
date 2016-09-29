#pragma once
#include <string>
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
};

