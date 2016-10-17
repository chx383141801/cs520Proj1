#include "sequentialheuristics.h"
#include "minihp.h"
#include "node.h"
#include <limits.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
SequentialHeuristics::SequentialHeuristics()
{
}

std::vector <node*> SequentialHeuristics::Succ(node &s)
{
    int x = s.x;
    int y = s.y;
    std::vector <node *> ret;

    if (x-1 < 0 || y+1 > 159)
        return ret;

    for (int i = 0; i < 3; i++)
    {
        ret.push_back(&array[x-1+i][y-1]);
        ret.push_back(&array[x-1+i][y+1]);
    }
    ret.push_back(&array[x-1][y]);
    ret.push_back(&array[x+1][y]);
    return ret;
}

//TODO: replace h0-h4 with four different heuristic functions
float SequentialHeuristics::Key(node *s, node *endpoint, int i, float weight) // Need to be done!
{
    if (i == 0)
    {
        return s->g[i] + calHn(s,endpoint,weight);
    }
    else if (i == 1)
    {
        return s->g[i] + calHn1(s,endpoint,weight);
    }
    else if (i == 2)
    {
        return s->g[i] + calHn2(s,endpoint,weight);
    }
    else if (i == 3)
    {
        return s->g[i] + calHn3(s,endpoint,weight);
    }
    else if (i == 4)
    {
        return s->g[i] + calHn4(s,endpoint,weight);
    }
}

void SequentialHeuristics::expandState(node &s, node *endpoint, int i, float weight)
{
    std::vector <node*>::iterator it;
    std::vector <node*> vect = Succ(s);
    for (it = vect.begin() ; it != vect.end() ; it++)
    {
        //first if is done if we initialize the g and bp in readmap
        //TODO: modify or rewrite readmap() function to initialize g[i] and bp[i]
        node *n = *it;
        if (n->g[i] > s.g[i] + calC(&s, n))
        {
            n->g[i] = s.g[i] + calC(&s, n);
            n->bp[i] = &s;
            if (closed[i].contains(*n) == false)
            {
                n->f[i] = Key(n,endpoint, i,weight);
                open[i].insert(*n);
            }
        }
    }
}

bool SequentialHeuristics::findPath(std::string path, float weight1, float weight2)
{
    //float weight1 = 1.0;
    //float weight2 = 1.0; // TODO: Need to be modified
    node *startpoint;
    node *endpoint;

    startpoint = &array[sttpt.first][sttpt.second];
    endpoint= &array[ndpt.first][ndpt.second];

    for (int i = 0 ; i < 5 ; i++)
    {
        startpoint->g[i] = 0;
        endpoint->g[i] = FLT_MAX;
        startpoint->bp[i] = NULL;
        endpoint->bp[i] = NULL;

        open[i].clear();
        closed[i].clear();

        startpoint->f[i] = Key(startpoint, endpoint, i, weight1);
        startpoint->h[i] = startpoint->f[i] - startpoint->g[i];
        open[i].insert(*startpoint);
    }

    while (open[0].size() != 0)
    {
        for (int i = 1 ; i < 5 ; i++)
        {
            if (open[i].peek().f[i] <= weight2 * open[0].peek().f[0])
            {
                if (endpoint->g[i] <= open[i].peek().f[i])
                    if (endpoint->g[i] < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file
                        node* temp = endpoint;
                        std::ofstream out("C:/Users/Yi Dang/Documents/GitHub/cs520Proj1/Project1/path.txt");//save the path to file

                        int path_len_nodes=1;
                        int path_len_distance;
                        int expanded_nodes=0;

                         path_len_distance=temp->g[i];
                        if (out.is_open()) out <<temp->g[i]<< "\n";

                        while (temp->parent != temp) {
                //		cout << temp->x << "," << temp->y << "," << temp->weight << "," << temp->gN << endl;
                            if (out.is_open())
                            {
                                out <<"("<< temp->x <<","<< temp->y << ")"<< "," << temp->weight <<"\n";


                            }
                            temp = temp->parent;
                            path_len_nodes++;
                        }
                        out << "(" << temp->x << "," << temp->y << ")" << "," << temp->weight << "\n";
            //			cout << temp->x << "," << temp->y << "," <<temp->weight<<","<< temp->gN << endl;
            //            cout<< temp->gN << endl;
            //            cout << "succcccccccc";
                        out.close();


                        std::ofstream data("C:/Users/Yi Dang/Documents/GitHub/cs520Proj1/Project1/data.txt", std::ios::app);//save relevant data to file
                       for (int ii=0;ii<5;ii++){
                            expanded_nodes+=closed[ii].size();
                       }

                        if (data.is_open()) out <<temp->g[i]<< "\n";
                        data<<path_len_distance<<","<<path_len_nodes<<","<<expanded_nodes<<"\n";


                         return true;
                    }
                else
                    {
                        node s = open[i].pop();
                        expandState(s, endpoint, i, weight1);
                        closed[i].insert(s);
                    }
            }
            else
            {
                if (endpoint->g[0] <= open[0].peek().f[0])
                    if (endpoint->g[0] < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file
                        node* temp = endpoint;
                        std::ofstream out("C:/Users/Yi Dang/Documents/GitHub/cs520Proj1/Project1/path.txt");//save the path to file

                        int path_len_nodes=1;
                        int path_len_distance;
                        int expanded_nodes;

                         path_len_distance=temp->g[0];
                        if (out.is_open()) out <<temp->g[0]<< "\n";

                        while (temp->parent != temp) {
                //		cout << temp->x << "," << temp->y << "," << temp->weight << "," << temp->gN << endl;
                            if (out.is_open())
                            {
                                out <<"("<< temp->x <<","<< temp->y << ")"<< "," << temp->weight <<"\n";


                            }
                            temp = temp->parent;
                            path_len_nodes++;
                        }
                        out << "(" << temp->x << "," << temp->y << ")" << "," << temp->weight << "\n";
            //			cout << temp->x << "," << temp->y << "," <<temp->weight<<","<< temp->gN << endl;
            //            cout<< temp->gN << endl;
            //            cout << "succcccccccc";
                        out.close();


                        std::ofstream data("C:/Users/Yi Dang/Documents/GitHub/cs520Proj1/Project1/data.txt", std::ios::app);//save relevant data to file
                        for (int ii=0;ii<5;ii++){
                             expanded_nodes+=closed[ii].size();
                        }
                        if (data.is_open()) out <<temp->g[0]<< "\n";
                        data<<path_len_distance<<","<<path_len_nodes<<","<<expanded_nodes<<"\n";
                         return true;
                    }
                else
                    {
                        node s = open[0].pop();
                        expandState(s, endpoint, 0, weight1);
                        closed[0].insert(s);
                    }
            }
        }
    }
return false;
}

//TODO: replace 1.0 with those 5 heuristic functions
float SequentialHeuristics::calHn(node *cur, node *des, float weight)
{
    //return weight * 1.0;
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=(std::abs(x1-x2)+std::abs(y1-y2));
    res=res*0.25;
    return weight * res;//Manhattan distance with highway
}

float SequentialHeuristics::calHn1(node *cur, node *des, float weight)
{
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=(std::abs(x1-x2)+std::abs(y1-y2));

    return weight * res;//Manhattan distance
}

float SequentialHeuristics::calHn2(node *cur, node *des, float weight)
{
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float d= std::min(std::abs(x2 - x1), std::abs(y2 - y1));
    float s=std::abs(x1-x2)+std::abs(y1-y2);
    float du=std::sqrt(2);
     float su=1;
    float res=du*d+su*(s-2*d);
    return weight * res;//diagonal distance
}

float SequentialHeuristics::calHn3(node *cur, node *des, float weight)
{
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float d= std::min(std::abs(x2 - x1), std::abs(y2 - y1));
    float s=std::abs(x1-x2)+std::abs(y1-y2);
    float du=std::sqrt(2);
     float su=0.25;
    float res=du*d+su*(s-2*d);
    return weight * res;//diagonal distance with highway
}

float SequentialHeuristics::calHn4(node *cur, node *des, float weight)
{
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return weight * res;//Euclidean distance
}
