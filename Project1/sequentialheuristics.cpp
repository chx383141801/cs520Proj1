#include "sequentialheuristics.h"
#include "minihp.h"
#include "node.h"
#include <limits.h>
#include <vector>

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

}

//TODO: replace 1.0 with those 5 heuristic functions
float SequentialHeuristics::calHn(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float SequentialHeuristics::calHn1(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float SequentialHeuristics::calHn2(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float SequentialHeuristics::calHn3(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float SequentialHeuristics::calHn4(node *cur, node *des, float weight)
{
    return weight * 1.0;
}
