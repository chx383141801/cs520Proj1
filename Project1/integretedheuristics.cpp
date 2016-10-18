#include "integretedheuristics.h"
#include <limits.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
//#include <math>
#include "minihp.h"

IntegretedHeuristics::IntegretedHeuristics()
{
}

std::vector <node*> IntegretedHeuristics::Succ(node &s)
{
    std::vector <node *> ret;

     for (int i = -1; i < 2; i++)
     {
         for (int j = -1; j < 2; j++)
         {
             if (i == 0 && j == 0) continue;
              int x = s.x + i;
              int y = s.y + j;
               std::cout<<"x"<<x<<"y"<<y<<std::endl;

            if (x >= 0 && x < 120 && y >= 0 && y < 160){
                if (array[x][y].weight != 0)
                {
                    ret.push_back(&array[x][y]);
                }
            }
         }
     }
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
    s.expand_counter++;
    for (int i = 0 ; i < 5 ; i++)
    {
        if (open[i].contains(&s,i) == true)
        {
            open[i].erase(&s,i);
        }
    }
    for (it = vect.begin() ; it != vect.end() ; it++)
    {
        node *n = *it;
        if (n->gN > s.gN + calC(&s, n))
        {
            n->gN = s.gN + calC(&s, n);
            n->parent = &s;
            if (closed_anchor.contains(n,0) == false)
            {
                n->f[0] = Key(n,endpoint, 0,weight1);
                open[0].insert(n,0);
                if (closed_inad.contains(n,0) == false)
                {
                    for (int i = 1 ; i < 5; i++)
                    {
                        float t1 = Key(n,endpoint, i,weight1);
                        float t2 = weight2 * Key(n, endpoint, 0,weight1);
                        if (Key(n,endpoint, i,weight1) <= weight2 * Key(n, endpoint, 0,weight1))
                        {
                            n->f[i] = Key(n,endpoint, i,weight1);
                            open[i].insert(n,i);
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
        open[i].insert(startpoint,i);
    }

    closed_anchor.clear();
    closed_inad.clear();

    while (open[0].size(0) != 0)
    {
        for (int i = 1 ; i < 5 ; i++)
        {
            if (open[i].size(i) > 0 && open[i].peek(i)->f[i] <= weight2 * open[0].peek(0)->f[0])
            {
                if (endpoint->gN <= open[i].peek(i)->f[i])
                {
                    if (endpoint->gN < FLT_MAX)
                    {
                        node* temp = endpoint;
                        std::ofstream out(path);//save the path to file

                        int path_len_nodes=1;
                        int path_len_distance;
                        int expanded_nodes=0;

                        path_len_distance=temp->gN;
                        if (out.is_open()) out <<temp->gN<< "\n";

                        while (temp->parent != NULL) {
                            //		cout << temp->x << "," << temp->y << "," << temp->weight << "," << temp->gN << endl;
                            if (out.is_open())
                            {
                                out <<"("<< temp->x <<","<< temp->y << ")"<< "," << temp->weight <<"\n";
                            }
                            temp = temp->parent;
                            path_len_nodes++;
                        }
                        out << "(" << temp->x << "," << temp->y << ")" << "," << temp->weight << "\n";

                        out.close();
                        std::string data_path = path.substr(0,path.find(".txt"));
                        data_path += "_data.txt";
                        std::ofstream data(data_path, std::ios::app);//save relevant data to file
                        expanded_nodes=closed_anchor.size(0)+closed_inad.size(1);
                        if (data.is_open())
                        {
                            data << "===============   closed  anchor    =================" << std::endl;
                            while (closed_anchor.size(0)!= 0)
                            {
                               node * n = closed_anchor.pop(0);
                               data << n->x << "," << n->y << " " << "expd_time: " << n->expand_counter << std::endl;
                            }
                            data << "=============== closed inadmissible =================" << std::endl;
                            while (closed_inad.size(1) != 0)
                            {
                                node * n = closed_inad.pop(1);
                                data << n->x << "," << n->y << " " << "expd_time: " << n->expand_counter << std::endl;
                            }
                            data << temp->gN<< "\n";
                            data<<path_len_distance<<","<<path_len_nodes<<","<<expanded_nodes<<"\n";
                        }

                        data.close();
                        return true;
                    }                }
                else
                    {
                        node *s = open[i].pop(i);
                        expandState(*s, endpoint, i, weight1, weight2);
                        closed_inad.insert(s,1);
                    }
            }
            else
            {
                if (endpoint->gN <= open[0].peek(0)->f[0])
                {
                    if (endpoint->gN < FLT_MAX)
                    {
                        node* temp = endpoint;
                        std::ofstream out(path);//save the path to file

                        int path_len_nodes=1;
                        int path_len_distance;
                        int expanded_nodes=0;

                        path_len_distance=temp->gN;
                        if (out.is_open()) out <<temp->gN<< "\n";

                        while (temp->parent != NULL) {
                            if (out.is_open())
                            {
                                out <<"("<< temp->x <<","<< temp->y << ")"<< "," << temp->weight <<"\n";
                            }
                            temp = temp->parent;
                            path_len_nodes++;
                        }
                        out << "(" << temp->x << "," << temp->y << ")" << "," << temp->weight << "\n";

                        out.close();

                        std::string data_path = path.substr(0,path.find(".txt"));
                        data_path += "_data.txt";
                        std::ofstream data(data_path, std::ios::app);//save relevant data to file
                        expanded_nodes=closed_anchor.size(0)+closed_inad.size(1);
                        if (data.is_open())
                        {
                            data << "===============   closed  anchor    =================" << std::endl;
                            while (closed_anchor.size(0)!= 0)
                            {
                               node * n = closed_anchor.pop(0);
                               data << n->x << "," << n->y << " " << "expd_time: " << n->expand_counter << std::endl;
                            }
                            data << "=============== closed inadmissible =================" << std::endl;
                            while (closed_inad.size(1) != 0)
                            {
                                node * n = closed_inad.pop(1);
                                data << n->x << "," << n->y << " " << "expd_time: " << n->expand_counter << std::endl;
                            }
                            data << temp->gN<< "\n";
                            data<<path_len_distance<<","<<path_len_nodes<<","<<expanded_nodes<<"\n";
                        }

                         return true;
                    }
                }
                else
                {
                    node *s = open[0].pop(0);
                    expandState(*s, endpoint, 0, weight1, weight2);
                    closed_anchor.insert(s,0);
                }
            }
        }
    }
return false;
}

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
