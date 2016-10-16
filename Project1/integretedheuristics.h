#ifndef INTEGRETEDHEURISTICS_H
#define INTEGRETEDHEURISTICS_H
#include "node.h"
#include "doastar.h"
#include "minihp.h"

#define NUM_OF_HEURISTICS 5

class IntegretedHeuristics : public doastar
{
public:
    IntegretedHeuristics();
    minihp <node> open[NUM_OF_HEURISTICS];
    minihp <node> closed_anchor;
    minihp <node> closed_inad;

    bool findPath(std::string path, float weight1, float weight2);
    std::vector<node *> Succ(node &s); //return successors of node s
    float Key(node *s, node *endpoint, int i, float weight);
    void expandState(node &s, node *endpoint, int i, float weight1, float weight2);

    float calHn(node *cur, node *des, float weight);
    float calHn1(node *cur, node *des, float weight);
    float calHn2(node *cur, node *des, float weight);
    float calHn3(node *cur, node *des, float weight);
    float calHn4(node *cur, node *des, float weight);
};

#endif // INTEGRETEDHEURISTICS_H
