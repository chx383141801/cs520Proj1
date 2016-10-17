#ifndef SEQUENTIALHEURISTICS_H
#define SEQUENTIALHEURISTICS_H
#include "doastar.h"
#include "minihp.h"
#include "node.h"
#include <vector>

#define NUM_OF_HEURISTICS 5

class SequentialHeuristics : public doastar
{
public:
    SequentialHeuristics();
    minihp <node> open[NUM_OF_HEURISTICS];
    minihp <node> closed[NUM_OF_HEURISTICS];

    bool findPath(std::string path, float weight1, float weight2);
    std::vector<node *> Succ(node &s); //return successors of node s
    float Key(node *s, node* endpoint, int i, float weight);
    void expandState(node &s, node *endpoint, int i, float weight);

    float calHn(node *cur, node *des, float weight);
    float calHn1(node *cur, node *des, float weight);
    float calHn2(node *cur, node *des, float weight);
    float calHn3(node *cur, node *des, float weight);
    float calHn4(node *cur, node *des, float weight);
};

#endif // SEQUENTIALHEURISTICS_H
