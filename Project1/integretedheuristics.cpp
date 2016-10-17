#include "integretedheuristics.h"
#include <limits.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
//#include <math>
IntegretedHeuristics::IntegretedHeuristics()
{
/*    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 160 ;j++)
        {
            array[i][j].fN=array[i][j].gN=array[i][j].hN=FLT_MAX;
             for (int k = 0; k < 160 ;k++){
             array[i][j].f[k]=array[i][j].g[k]=array[i][j].h[k]=FLT_MAX;
             array[i][j].bp[k]=nullptr;
             }
        }
    }*/
}


std::vector <node*> IntegretedHeuristics::Succ(node &s)
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

float IntegretedHeuristics::Key(node *s, node* endpoint, int i, float weight) // Need to be done!
{
    if (i == 0)
    {
        return s->gN + calHn(s, endpoint, weight);
    }
    else if (i == 1)
    {
        return s->gN + calHn1(s, endpoint, weight);
    }
    else if (i == 2)
    {
        return s->gN + calHn2(s, endpoint, weight);
    }
    else if (i == 3)
    {
        return s->gN + calHn3(s, endpoint, weight);
    }
    else if (i == 4)
    {
        return s->gN + calHn4(s, endpoint, weight);
    }
}

//We use gN and parent in node instead of g and bp array here
void IntegretedHeuristics::expandState(node &s, node *endpoint, int i, float weight1, float weight2)
{
    std::vector <node*>::iterator it;
    std::vector <node*> vect = Succ(s);
    for (it = vect.begin() ; it != vect.end() ; it++)
    {
        //first 'if' is done if we initialize the gN and parent in readmap
        //TODO: modify or rewrite readmap() function to initialize gN and parent
        node *n = *it;
        if (n->gN > s.gN + calC(&s, n))
        {
            n->gN = s.gN + calC(&s, n);
            n->parent = &s;
            if (closed_anchor.contains(*n) == false)
            {
                n->f[0] = Key(n,endpoint, 0,weight1);
                open[0].insert(*n);
                if (closed_inad.contains(*n) == false)
                {
                    for (int i = 1 ; i < 5; i++)
                    {
                        if (Key(n,endpoint, i,weight1) <= weight2 * Key(n, endpoint, 0,weight1))
                        {
                            n->f[i] = Key(n,endpoint, i,weight1);
                            open[i].insert(*n);
                        }
                    }
                }
            }
        }
    }
}

bool IntegretedHeuristics::findPath(std::string path, float weight1, float weight2)
{
    //float weight1 = 1.0;
    //float weight2 = 1.0; // TODO: Need to be modified
    node *startpoint;
    node *endpoint;

    startpoint = &array[sttpt.first][sttpt.second];
    endpoint= &array[ndpt.first][ndpt.second];

    startpoint->gN = 0;
    endpoint->gN = FLT_MAX;
    startpoint->parent = NULL;
    endpoint->parent = NULL;

    for (int i = 0 ; i < 5 ; i++)
    {
        open[i].clear();

        startpoint->f[i] = Key(startpoint, endpoint, i, weight1);
        startpoint->h[i] = startpoint->f[i] - startpoint->g[i];
        open[i].insert(*startpoint);
    }

    closed_anchor.clear();
    closed_inad.clear();

    while (open[0].size() != 0)
    {
        for (int i = 1 ; i < 5 ; i++)
        {
            if (open[i].peek().f[i] <= weight2 * open[0].peek().f[0])
            {
                if (endpoint->gN <= open[i].peek().f[i])
                {
                    if (endpoint->gN < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file

                                        node* temp = endpoint;
                                        std::ofstream out("C:/Users/Yi Dang/Documents/GitHub/cs520Proj1/Project1/path.txt");//save the path to file

                                        int path_len_nodes=1;
                                        int path_len_distance;
                                        int expanded_nodes=0;

                                         path_len_distance=temp->gN;
                                        if (out.is_open()) out <<temp->gN<< "\n";

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
                                        expanded_nodes=closed_anchor.size()+closed_inad.size();
                                        if (data.is_open()) out <<temp->gN<< "\n";
                                        data<<path_len_distance<<","<<path_len_nodes<<","<<expanded_nodes<<"\n";

                        return true;
                    }
                }
                else
                    {
                        node s = open[i].pop();
                        expandState(s, endpoint, i, weight1, weight2);
                        closed_inad.insert(s);
                    }
            }
            else
            {
                if (endpoint->gN <= open[0].peek().f[0])
                {
                    if (endpoint->gN < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file

                         return true;
                    }
                }
                else
                {
                    node s = open[0].pop();
                    expandState(s, endpoint, 0, weight1, weight2);
                    closed_anchor.insert(s);
                }
            }
        }
    }
return false;
}

//TODO: replace 1.0 with those 5 heuristic functions
float IntegretedHeuristics::calHn(node *cur, node *des, float weight)
{
    //return weight * 1.0;
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=(std::abs(x1-x2)+std::abs(y1-y2));
    res=res*0.25;
    return weight * res;//Manhattan distance with highway
}

float IntegretedHeuristics::calHn1(node *cur, node *des, float weight)
{
    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=(std::abs(x1-x2)+std::abs(y1-y2));

    return weight * res;//Manhattan distance
}

float IntegretedHeuristics::calHn2(node *cur, node *des, float weight)
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

float IntegretedHeuristics::calHn3(node *cur, node *des, float weight)
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

float IntegretedHeuristics::calHn4(node *cur, node *des, float weight)
{

    float x1=cur->x,x2=des->x;
    float y1=cur->y,y2=des->y;
    float res=std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return weight * res;//Euclidean distance
}
