#include "weightedastar.h"
#include "node.h"
#include <string>
#include <iostream>
#include <fstream>
#include<set>
#include <sstream>
//#include<math>
#define Maximum 10000

weightedAStar::weightedAStar()
{
}

bool weightedAStar::findPath(double weight, double &cost,int &nodes,int &closed)
{
    node *startpoint;
    node *endpoint;

    startpoint = &array[sttpt.first][sttpt.second];
    endpoint= &array[ndpt.first][ndpt.second];

    std::set<node*> openList;
    std::set<node*> closedList;
    openList.clear();
    closedList.clear();


    startpoint->gN = 0;
    startpoint->hN = calHn(startpoint, endpoint, weight);
    startpoint->fN = startpoint->gN + startpoint->hN;
//	cout << startpoint->gN << "," << startpoint->hN << "," << startpoint->fN <<"asdasdasd"<< endl;
    startpoint->parent = startpoint;


    openList.insert(startpoint);

    node *s;
    while (openList.size()>0)
    {
    //	cout <<"openList.size:" <<openList.size() << endl;

        s=findLowestNode(openList);

    //	cout << "pop s:(" << s->x << "," << s->y << ")" << endl;

        if (s == endpoint) {
            node* temp = endpoint;
            cost = temp->gN;

            while (temp->parent != temp){
                temp=temp->parent;
                nodes++;
            }
closed=closedList.size();
            return true;
        }




        closedList.insert(s);

    //    std::cout << closedList.size() << std::endl;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) continue;
                int xCur = s->x + i;
                int yCur = s->y + j;
                //cout << "check-" << xCur << "," << yCur;
                //cout <<xCur<<endl;
                //cout << i << "," << j << endl;
                //cout << "check:" << xCur << "," << yCur <<","<< array[xCur][yCur].weight<<endl;
                if (xCur >= 0 && xCur < 120 && yCur >= 0 && yCur < 160) {
                    if (array[xCur][yCur].weight == '0') continue;
                //	cout <<"x,y:"<< xCur << "," << yCur << ":" << array[xCur][yCur].weight << endl;
                //	cout << "check:" << xCur << "," << yCur<<endl;
                    node *s_ = &array[xCur][yCur];
                    s_->hN = calHn(s_,endpoint, weight);
                    if(closedList.find(s_)==closedList.end())
                    {
                    //	cout << "s_ not in close" << endl;
                        if (openList.find(s_) == openList.end())
                        {
                    //		cout << "s_ not in open" << endl;
                            s_->gN = Maximum;
                            s_->parent = nullptr;
                        }

                        //cout << "here";


                        float css_ = calC(s, s_);
                        if (s->gN + css_ < s_->gN)
                        {
                            s_->gN = s->gN + css_;
                            s_->parent = s;
                            //cout << "here";

                            if (openList.find(s_) != openList.end())
                            {
                                //	cout << "here";

                                openList.erase(s_);

                            }
                            s_->fN = s_->gN + s_->hN;
                            openList.insert(s_);
                        }

                    }

                    //	cout << "" << << endl;
                }

            }
        }
    }

    return false;
}

bool weightedAStar::findPath(double weight, std::string path)
{
    node *startpoint;
    node *endpoint;

    startpoint = &array[sttpt.first][sttpt.second];
    endpoint= &array[ndpt.first][ndpt.second];

    std::set<node*> openList;
    std::set<node*> closedList;
    openList.clear();
    closedList.clear();


    startpoint->gN = 0;
    startpoint->hN = calHn(startpoint, endpoint, weight);
    startpoint->fN = startpoint->gN + startpoint->hN;
//	cout << startpoint->gN << "," << startpoint->hN << "," << startpoint->fN <<"asdasdasd"<< endl;
    startpoint->parent = startpoint;


    openList.insert(startpoint);

    node *s;
    while (openList.size()>0)
    {
    //	cout <<"openList.size:" <<openList.size() << endl;

        s=findLowestNode(openList);

    //	cout << "pop s:(" << s->x << "," << s->y << ")" << endl;

        if (s == endpoint) {

        //	cout << "this is the end"<< endl;

            node* temp = endpoint;
            std::ofstream out(path);
            std::string info_path = path.substr(0,path.find(".txt"));
            info_path += "_info.txt";
            std::ofstream out_info(info_path);

            if (out.is_open()) out <<temp->gN<< "\n";

            while (temp->parent != temp) {
            //	cout << temp->x << "," << temp->y << "," << temp->weight << "," << temp->gN << endl;
                if (out.is_open())
                {
                    out <<"("<< temp->x<<","<< temp->y<< ")\n";
                }
                if (out_info.is_open())
                {
                    out_info <<"("<< temp->x<<","<< temp->y<< ")" << " " << temp->gN << "," << temp->hN << std::endl;
                }

                temp = temp->parent;
            }
            out << "(" << temp->x<< "," << temp->y<< ")\n";
            out_info <<"("<< temp->x<<","<< temp->y<< ")" << " " << temp->gN << "," << temp->hN << std::endl;
            //cout << temp->x << "," << temp->y << "," <<temp->weight<<","<< temp->gN << endl;

            out.close();
            out_info.close();
            return true;
        }




        closedList.insert(s);

    //	cout << "closedList.insert(s);" << endl;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) continue;
                int xCur = s->x + i;
                int yCur = s->y + j;
                //cout << "check-" << xCur << "," << yCur;
                //cout <<xCur<<endl;
                //cout << i << "," << j << endl;
                //cout << "check:" << xCur << "," << yCur <<","<< array[xCur][yCur].weight<<endl;
                if (xCur >= 0 && xCur < 120 && yCur >= 0 && yCur < 160) {
                    if (array[xCur][yCur].weight == '0') continue;
                //	cout <<"x,y:"<< xCur << "," << yCur << ":" << array[xCur][yCur].weight << endl;
                //	cout << "check:" << xCur << "," << yCur<<endl;
                    node *s_ = &array[xCur][yCur];
                    s_->hN = calHn(s_,endpoint, weight);
                    if(closedList.find(s_)==closedList.end())
                    {
                    //	cout << "s_ not in close" << endl;
                        if (openList.find(s_) == openList.end())
                        {
                    //		cout << "s_ not in open" << endl;
                            s_->gN = Maximum;
                            s_->parent = nullptr;
                        }

                        //cout << "here";


                        float css_ = calC(s, s_);
                        if (s->gN + css_ < s_->gN)
                        {
                            s_->gN = s->gN + css_;
                            s_->parent = s;
                            //cout << "here";

                            if (openList.find(s_) != openList.end())
                            {
                                //	cout << "here";

                                openList.erase(s_);

                            }
                            s_->fN = s_->gN + s_->hN;
                            openList.insert(s_);
                        }

                    }

                    //	cout << "" << << endl;
                }

            }
        }
    }
    return false;
}

float weightedAStar::calHn(node *cur, node *des, double weight)
{	//calculate the Hn
   // return weight *(std::abs(des->x - cur->x) + std::abs(des->y - cur->y)) * 0.25 ;
    int dx = std::abs(des->x - cur->x);
   int dy =  std::abs(des->y - cur->y);
   //return weight*(dx+dy)/4;
   //return weight*sqrt(dx*dx+dy*dy);

    //return weight*(dx+dy+0.4*(dx<dy?dx:dy)-0.75*(dx+dy-2*dx<dy?dx:dy));
   // return weight*(dx+dy-0.6*(dx<dy?dx:dy));
   return weight*(dx+dy+0.9*(dx<dy?dx:dy));
}
