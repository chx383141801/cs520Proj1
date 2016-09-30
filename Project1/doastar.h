#ifndef DOASTAR_H
#define DOASTAR_H
#include<set>
//#include <math>
#include "node.h"


using namespace std;

class doastar{


public:
node (*array)[160];
pair<int, int> sttpt;
pair<int, int> ndpt;
doastar();
~doastar();

bool readMap();
bool findPath();

node * findLowestNode(set<node*>& ns);

float calHn(node * cur, node * des);

float calC(node * cur, node * des);




};

#endif // DOASTAR_H
