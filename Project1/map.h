#ifndef MAP_H
#define MAP_H
#include "node.h"
#include <string>
#include <vector>
#include <QGraphicsScene>

class map
{
public:
    map();
    ~map();
    int mapCreator();
    void randomSelectHard(node (*array)[160], int row, int column, int amount); // get the 'amount' number ofrandom nodes from given map array
    int randomSelectHighway(node (*array)[160], int row, int column, int index);
    void randomSelectBlock(node (*array)[160], int row, int column);
    void randomSelectStartAndGoal();
    void mapWriter();
    void mapLoader(std::string path, QGraphicsScene *scene);
    std::vector<std::string> split(std::string s, std::string delim);
    double rnd1(double *r);

    node (*array)[160];
    std::vector <int> start;
    std::vector <int> goal;
    std::vector <int> hdCenter;
};

#endif
