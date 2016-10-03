#ifndef DOASTAR_H
#define DOASTAR_H
#include<set>
#include <string>
#include "node.h"

class doastar{

public:
node (*array)[160];
std::pair<int, int> sttpt;
std::pair<int, int> ndpt;
doastar();
~doastar();
bool readMap(std::string path);
bool findPath(std::string path);
node * findLowestNode(std::set<node*>& ns);
float calHn(node * cur, node * des);
float calC(node * cur, node * des);

};

#endif // DOASTAR_H
