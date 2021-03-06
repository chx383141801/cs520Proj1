#include "doastar.h"
//#include "coordinate.h"
#include <QDebug>
#include <string>  
#include <iostream>
#include <fstream>
#include <iostream>
#include<set>
#include <sstream>
#include <limits.h>
//#include<math>
#define Maximum 10000


	doastar::doastar(){
		array = new node[120][160];
		for (int i = 0; i < 120; i++)
		{
			for (int j = 0; j < 160 ;j++)
			{
				array[i][j].x = i;
				array[i][j].y = j;
                array[i][j].fN = FLT_MAX;
                array[i][j].gN = FLT_MAX;
                array[i][j].hN = FLT_MAX;
                array[i][j].expand_counter = 0;

                for (int k = 0; k < 160 ;k++)
                {
                    array[i][j].f[k]=array[i][j].g[k]=array[i][j].h[k]=FLT_MAX;
                    array[i][j].bp[k]=nullptr;
                }
			}
		}
	}


	doastar:: ~doastar() {
	}
//TODO: Initialize each node coordinate x,y and
//TODO: Initialize the g[i] with FLT_MAX, bp[i] = NULL
    bool doastar::readMap(std::string path)
	{
	//	cout << "read start" << endl;
        std::ifstream in(path);

		if (!in)
		{
            std::cerr << "some errors happened";
			in.close();
			return false;
		}
        std::string str;
	
		int countr = 0;//row
        while (std::getline(in, str))
		{
			if (countr==0|| countr == 1)
			{
				int x, y;
				int spps = str.find(" ");
                std::stringstream ss;
				ss<<str.substr(0, spps);
				ss >> x;
				ss.clear();
				ss << str.substr(spps+1, str.size()-1);
				ss >> y;
				if (countr == 0) {
					sttpt.first = x;
					sttpt.second = y;
				}
				else {
					ndpt.first = x;
					ndpt.second = y;
				}
			}
            if (countr++ > 10) {

				int countc = 0;//column

			//	cout << str << endl;

				for (int i = 0; i<str.size() ; i++) {
					
					
					char ith = str.at(i);
					if (ith == ',') continue;
				//	cout << countr - 11 << "," << countc << endl;
                    if (countr - 12 >= 120|| countc >= 160) break;
                    array[countr - 12][countc++].weight = ith;
					if (ith == 'a' || ith == 'b') i++;

				//	for (int j = 0; j < countc; j++) cout << ith;

					//array[count - 11][i].weight = str.at(i);
			
				}
			//	for (int j = 0; j < countc; j++) cout << array[countr - 11][j].weight;
			//	cout << endl;
			}
		
		}
		for (int i = 0; i < 120; i++)
		{
			for (int j = 0; j < 160; j++)
			{
			//	cout << "("<< array[i][j].x<<","<< array[i][j].y<<")";
           // std::cout <<  array[i][j].weight;
//std::cout << "123123123";
			}
	//		cout << endl;
		}

  //      std::cout << "123123123";

		//cout << "read end" << endl;
		in.close();

		return true;
	}

	
    bool doastar::findPath(std::string path)
    {
		node *startpoint;
		node *endpoint;
std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx";
        startpoint = &array[sttpt.first][sttpt.second];
        endpoint= &array[ndpt.first][ndpt.second];

        std::set<node*> openList;
        std::set<node*> closedList;
		openList.clear();
		closedList.clear();
  //      std::cout<<"888888888888888888888888888888888888888888888888888888888888888888888888"<<std::endl;
//std::cout<<"888888888888888888888888888888888888888888888888888888888888888888888888"<<std::endl;
//std::cout<<"888888888888888888888888888888888888888888888888888888888888888888888888"<<std::endl;
//std::cout<<"888888888888888888888888888888888888888888888888888888888888888888888888"<<std::endl;
		startpoint->gN = 0;
		startpoint->hN = calHn(startpoint, endpoint);
		startpoint->fN = startpoint->gN + startpoint->hN;
	//	cout << startpoint->gN << "," << startpoint->hN << "," << startpoint->fN <<"asdasdasd"<< endl;
		startpoint->parent = startpoint;


		openList.insert(startpoint);


	//	cout << "start." << startpoint->x<<","<< startpoint-> y << endl << endl << endl;

		node *s;
		while (openList.size()>0) {
			
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
						s_->hN = calHn(s_,endpoint);
						if(closedList.find(s_)==closedList.end()){
						//	cout << "s_ not in close" << endl;
							if (openList.find(s_) == openList.end()) {
						//		cout << "s_ not in open" << endl;
								s_->gN = Maximum;
								s_->parent = nullptr;
							}

							//cout << "here";


						float css_ = calC(s, s_);
						if (s->gN + css_ < s_->gN) {
							s_->gN = s->gN + css_;
							s_->parent = s;
							//cout << "here";

							if (openList.find(s_) != openList.end()) {
							//	cout << "here";

								openList.erase(s_);

							}
							s_->fN = s_->gN + s_->hN;
							openList.insert(s_);
				//			cout << "this time insert" << s_->x << "," << s_->y<<",gN:"<<s_->gN<<",fN:"<<s_->fN<< endl;
						//	s->hN = calHn(s, endpoint);
						//	s_->fN = s_->gN + s_->hN;
							
							
							
						//	cout << "openlist size:" <<openList.size() << endl;
						//	cout << xCur << "," << yCur << ":" << array[xCur][yCur].weight <<"end" << endl << endl << endl << endl << endl;
						}
						
						}
					
					//	cout << "" << << endl;
					}
				
				}
			}
			
			

		}
		return false;

	}

    node *doastar::findLowestNode(std::set<node*> &ns) {
		node * lowest=new node();
		lowest->fN = 100000;
	//	cout << "findLN:size before:" << ns.size() << endl;
		for each (node* n in ns)
		{
			//cout << "(" << n->x << "," << n->y << "):" << n->fN <<".weight:"<<n->weight <<endl;
		//	cout << "nfn now:" << n->fN << endl;
            if (lowest->fN > n->fN){
				lowest = n;
		//		cout << "lowest now:" << lowest->fN<<endl;
			}
		}
		ns.erase(lowest);
	//	cout << "findLN:size after:" << ns.size() << endl;
		return lowest;
	}


	float doastar::calHn(node *cur, node *des) {	//calculate the Hn
        int dx = std::abs(des->x - cur->x);
       int dy =  std::abs(des->y - cur->y);
       //return dy+ dx;
std::cout<<dx+dy+0.4*(dx<dy?dx:dy)<<std::endl;
//std::cout<<"888888888888888888888888888888888888888888888888888888888888888888888888"<<std::endl;


        return dx+dy+0.4*(dx<dy?dx:dy);
       //return (dx+dy)*(dx+dy);

	}

	float doastar::calC(node *cur, node *next) {	//calculate the C(s,s`)
		char cw = cur->weight;
		char nw = next->weight;
		int cx = cur->x;
		int cy = cur->y;
		int nx = next->x;
		int ny = next->y;

		float distance = Maximum;

		if (cw == '0'|| nw == '0') return Maximum;
        if (std::abs(ny - cy) + std::abs(nx - cx) == 2) {
			if (cw == '1' || cw == 'a') {
				if (nw == '1' || nw == 'a') return 1.4;
				else return 2.1;
			}

			else {
				if (nw == '1' || nw == 'a') return 2.1;
				else return 2.8;
			}

		}

		else {
			float tmp1, tmp2;
			float tmp3=1;
			if (cw == '1'|cw=='a') tmp1 = 0.5;
			else tmp1 = 1;
			if (nw == '1' | nw == 'a') tmp2 = 0.5;
			else tmp2 = 1;

			if ((cw == 'a' || cw == 'b') && (nw == 'a' || nw == 'b')) tmp3 = 0.25;
			return((tmp1 + tmp2)*tmp3);

		}
	}
