#ifndef WEIGHTEDASTAR_H
#define WEIGHTEDASTAR_H
#include <doastar.h>
#include <string>

class weightedAStar : public doastar
{
public:
    weightedAStar();
    bool findPath(double weight, std::string path);
    float calHn(node *cur, node *des, double weight);
};

#endif // WEIGHTEDASTAR_H
