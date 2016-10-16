#include "integretedheuristics.h"
#include <limits.h>

IntegretedHeuristics::IntegretedHeuristics()
{
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

//TODO: replace h0-h4 with four different heuristic functions
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
        //first if is done if we initialize the gN and parent in readmap
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
                    if (endpoint->gN < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file
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
                    if (endpoint->gN < FLT_MAX)
                    {
                        //TODO: terminate and return path and write file
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

}

//TODO: replace 1.0 with those 5 heuristic functions
float IntegretedHeuristics::calHn(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float IntegretedHeuristics::calHn1(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float IntegretedHeuristics::calHn2(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float IntegretedHeuristics::calHn3(node *cur, node *des, float weight)
{
    return weight * 1.0;
}

float IntegretedHeuristics::calHn4(node *cur, node *des, float weight)
{
    return weight * 1.0;
}
