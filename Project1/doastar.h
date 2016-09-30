#ifndef DOASTAR_H
#define DOASTAR_H
#include<set>
//#include <math>
#include "node.h"


using namespace std;

class doastar{


public:
node (*array)[160];
doastar();
~doastar();

bool readMap();
bool findPath(node *startpoint, node *endpoint);

node * findLowestNode(set<node*>& ns);

float calHn(node * cur, node * des);

float calC(node * cur, node * des);




};

#endif // DOASTAR_H
