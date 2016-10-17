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

    float g[5];
    float f[5];
    float h[5];
    node *bp[5];

    bool operator<(const node *nd) {
        return (fN < nd->fN);
	}

    bool operator>(const node *nd) {
        return (fN > nd->fN);
	}

    bool operator==(const node *nd) {
        return (x == nd->x&&y==nd->y);
	}

};



#endif // NODE_H
