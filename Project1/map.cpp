#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <utility>
#include <unordered_map>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>

#define random(x)(rand()%x)

map::map()
{
    array = new node[120][160];
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 160; j++)
        {
            array[i][j].weight = '1';
            array[i][j].isHighway = 'n';
        }
    }
}

map::~map()
{
    //delete array;
}

int map::mapCreator()
{
    //select Hard to traverse cells
    randomSelectHard(array, 120, 160, 8);

    //select Highway by calling function randomSelectHighway()
    int signal = 0;
    time_t t_start, t_current;
    t_start = time(NULL);
    for (int i = 0; i < 4; )
    {
        int ret = randomSelectHighway(array, 120, 160, i + 1);
        if (ret == 0)
        {
            i++;
            signal++;
            std::cout << "find " << signal << std::endl;
        }
        t_current = time(NULL);
        // allow 120 seconds to run for 4 paths
        if ((t_current - t_start) == 120)
        {
            for (int j = 0; j < 120; j++)
            {
                for (int k = 0; k < 160; k++)
                {
                    array[j][k].isHighway = 'n';
                }
            }
            signal = 0;
            std::cout << "time out restart..." << std::endl;
            i = 0;
            t_start = time(NULL);
        }
    }

    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 160; j++)
        {
            if (array[i][j].isHighway == 'a')
                array[i][j].weight = array[i][j].isHighway;
            else if (array[i][j].isHighway == 'b')
                array[i][j].weight = array[i][j].isHighway;
        }
    }

    //select blocked cells
    randomSelectBlock(array, 120, 160);
    randomSelectStartAndGoal();

    return 0;
}

int map::randomSelectHighway(node (*array)[160], int row, int column, int index)
{
    std::unordered_map <node*, int> isVisited;
    srand(unsigned(time(NULL)));
    double rnd_0 = random(100);
    double mark = rnd1(&rnd_0);
    int c = 0;
    int r = 0;
    int direction;
    int vOrh;
    int isSuccess = 0; // 0 on success; 1 on fail
    std::vector <node *> vect;
    std::vector <node*>::iterator it;

    //initialize the highway
    if (mark >= 0.5)
    {
        vOrh = 1; //go verticle
        direction = 1; //1 to go down or go right; 0 to go up or left
        c = (rnd1(&rnd_0) * 100) * column / 100 + 1; // to avoid starting the path along the boundary
    }
    else
    {
        vOrh = 0; //go horizontal
        direction = 1;
        r = (rnd1(&rnd_0) * 100) * row / 100 + 1;
    }

    // move to construct highway
    while (r >= 0 && r < row && c >= 0 && c < column)
    {
        if (vOrh == 1)
        {
            for (int j = 0; j < 20 && r < row && r >= 0; j++)
            {

                if (array[r][c].isHighway == 'n' && isVisited.find((&array[r][c])) == isVisited.end())
                {
                    isVisited[(&array[r][c])] = 1;
                    vect.push_back(&array[r][c]);
                    if (direction == 1)
                        r++;
                    else
                        r--;
                }
                else
                {
                    vect.clear();
                    isVisited.clear();
                    isSuccess = 1;
                    break;
                }
            }
        }
        else
        {
            for (int j = 0; j < 20 && c < column && c >= 0; j++)
            {
                if (array[r][c].isHighway == 'n' && isVisited.find((&array[r][c])) == isVisited.end())   //std::find(vect.begin(), vect.end(), &array[r][c]) == vect.end()
                {
                    isVisited[(&array[r][c])] = 1;
                    vect.push_back(&array[r][c]);
                    if (direction == 1)
                        c++;
                    else
                        c--;
                }
                else
                {
                    vect.clear();
                    isVisited.clear();
                    isSuccess = 1;
                    break;
                }
            }
        }

        if (isSuccess == 1)
            break;

        mark = rnd1(&rnd_0);
        if (mark > 0.6 && mark <= 0.8)
        {
            vOrh ^= 1;
            direction = 1;
        }
        else if (mark > 0.8 && mark <= 1.0)
        {
            vOrh ^= 1;
            direction = 0;
        }
    }

    if (vect.size() < 101)
    {
        isSuccess = 1;
        vect.clear();
        return isSuccess;
    }

    for (it = vect.begin(); it != vect.end(); it++)
    {
        node * n = *it;
        if (n->weight == '1')
        {
            n->isHighway = 'a';
            n->index = '0' + index;
        }
        else if (n->weight == '2')
        {
            n->isHighway = 'b';
            n->index = '0' + index;
        }
        else
            std::cout << "Exception on marking highway!" << std::endl;
    }

    return isSuccess;
}

void map::randomSelectHard(node (*array)[160], int row, int column, int amount)
{
    srand(unsigned(time(NULL)));
    double rnd_0 = random(6);;
    srand(unsigned(time(NULL) + 1));
    double rnd_1 = random(5);
    //generate 8 pairs of numbers for 8 nodes
    for (int i = 0; i < amount; i++)
    {
        double rnd_2 = 5.0;

        // plan 2
        int r = (rnd1(&rnd_0) * 100) * 89 / 100 + 16;
        int c = (rnd1(&rnd_1) * 100) * 129 / 100 + 16;

        //save the coordinate of center
        hdCenter.push_back(r);
        hdCenter.push_back(c);

        for (int j = r - 15; j < r + 15; j++)
        {
            for (int k = c - 15; k < c + 15; k++)
            {
                double mark = rnd1(&rnd_2);
                if (mark >= 0.5)
                {
                    array[j][k].weight = '2'; // when the random number is 1, we change the weight of the cell to 2
                }
            }
        }
    }
}

void map::randomSelectBlock(node (*array)[160], int row, int column)
{
    srand(unsigned(time(NULL)));
    double rnd_0 = random(10);
    double rnd_1 = random(12);

    int amount = row * column * 0.2;
    int r, c;

    for (int i = 0; i < amount;)
    {
        r = (rnd1(&rnd_0) * 100) * row / 100;
        c = (rnd1(&rnd_1) * 100) * column / 100;
        if (array[r][c].isHighway != 'a' && array[r][c].isHighway != 'b')
        {
            array[r][c].weight = '0';
            i++;
        }
    }
}

double map::rnd1(double *r)
{
    int m;
    double s, u, v, p;
    s = 65536.0; u = 2053.0; v = 13849.0;
    m = (int)(*r / s); *r = *r - m*s;
    *r = u*(*r) + v; m = (int)(*r / s);
    *r = *r - m*s; p = *r / s;
    return(p);
}

std::vector <std::string> map::split(std::string s, std::string delim)
{
    std::vector <std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0)
        return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

void map::mapWriter(std::string path)
{
    std::vector <std::pair<int,int>>::iterator it_start = start.begin();
    std::vector <std::pair<int,int>>::iterator it_goal = goal.begin();

    for (int i = 0 ; i < 10 && it_start != start.end() && it_goal != goal.end(); i++ , it_start++, it_goal++)
    {
        std::ofstream file;
        if (path == "")
        {
            std::string p = "map_";
            p += std::to_string(i);
            p += ".txt";
            file.open(p);
        }
        else
        {
            std::string p = path;
            p += "_";
            p += std::to_string(i);
            p += ".txt";
            file.open(p);
        }

        //write start coordinate
        std::pair <int,int> start_p = *it_start;
        file << start_p.first << ' ' << start_p.second << std::endl;

        //write goal coordinate
        std::pair <int,int> goal_p = *it_goal;
        file << goal_p.first << ' ' << goal_p.second << std::endl;

        int counter = 0;
        std::vector <int>::iterator it;
        //write hardtotraverse center
        for (it = hdCenter.begin(); it != hdCenter.end(); it++)
        {
            file << *it << ' ';
            ++counter;
            if (counter % 2 == 0)
                file << std::endl;
        }

        counter = 0;
        //write numbers of cells
        file << 120 << ',' << 160 << std::endl;

        //write 120*160 cells
        for (int i = 0; i < 120; i++)
        {
            for (int j = 0; j < 160; j++)
            {
                file << array[i][j].weight;
                if (array[i][j].weight == 'a' || array[i][j].weight == 'b')
                    file << array[i][j].index;
                if (j < 159)
                    file << ',';
                counter++;
                if (counter % 160 == 0)
                    file << std::endl;
            }
        }
        file.close();
    }
}

int map::mapLoader(std::string path, QGraphicsScene *scene)
{
    std::vector <std::string> svect;
    std::vector <std::string>::iterator it;
    std::ifstream file;
    file.open(path);
    if (file.is_open())
        std::cout << "file is open" << std::endl;
    else
    {
        std::cout << "file fail to open" << std::endl;
        return 1;
    }

    std::vector <std::string> strVect;

    for (int i = 0; i < 10; i++)
    {
        std::string str;
        std::getline(file, str);

        strVect.push_back(str);
    }
    std::string temp;
    std::getline(file, temp);

    for (int i = 0; i < 120; i++)
    {
        std::string str(160, '0');
        std::getline(file, str);
        svect = split(str, ",");
        it = svect.begin();
        std::string temp;
        for (int j = 0; j < 160 && it != svect.end(); j++, it++)
        {
            QGraphicsRectItem * rect = new QGraphicsRectItem();
            temp = *it;
            if (temp == "0")
            {
                rect->setRect(j * 10, i * 10, 10, 10);
                rect->setBrush(Qt::black);
            }
            else if (temp == "1")
            {
                rect->setRect(j * 10, i * 10, 10, 10);
                rect->setBrush(Qt::white);
            }
            else if (temp == "2")
            {
                rect->setRect(j * 10, i * 10, 10, 10);
                rect->setBrush(Qt::darkYellow);
            }
            else if (temp.find("a") != std::string::npos)
            {
                rect->setRect(j * 10, i * 10, 10, 10);
                rect->setBrush(Qt::green);
            }
            else if (temp.find("b") != std::string::npos)
            {
                rect->setRect(j * 10, i * 10, 10, 10);
                rect->setBrush(Qt::magenta);
            }
            scene->addItem(rect);
            //delete rect;
        }


    }
    it = strVect.begin();
    std::string recv = *it;
    std::vector <std::string> startOrGoal = split(recv, " ");
    std::vector <std::string>::iterator it_start_Or_Goal;
    it_start_Or_Goal = startOrGoal.begin();
    std::string string_x = *it_start_Or_Goal;
    it_start_Or_Goal++;
    std::string string_y = *it_start_Or_Goal;
    int start_x = atoi(string_x.c_str());
    int start_y = atoi(string_y.c_str());

    QGraphicsRectItem * rect_0 = new QGraphicsRectItem();
    rect_0->setRect(start_y*10, start_x * 10, 10, 10);
    rect_0->setBrush(Qt::blue);

    scene->addItem(rect_0);

    it++;
    recv = *it;
    startOrGoal.clear();
    startOrGoal = split(recv, " ");
    it_start_Or_Goal = startOrGoal.begin();
    string_x = *it_start_Or_Goal;
    it_start_Or_Goal++;
    string_y = *it_start_Or_Goal;
    int goal_x = atoi(string_x.c_str());
    int goal_y = atoi(string_y.c_str());

    QGraphicsRectItem * rect_1 = new QGraphicsRectItem();
    rect_1->setRect(goal_y*10, goal_x * 10, 10, 10);
    rect_1->setBrush(Qt::red);

    scene->addItem(rect_1);
    file.close();
    return 0;
}

int map::mapAndPathLoader(std::string mapDirect, std::string pathDirect, QGraphicsScene *scene, double &cost)
{
    mapLoader(mapDirect, scene);
    std::ifstream file;
    file.open(pathDirect);
    if (file.is_open())
        std::cout << "path file is open" << std::endl;
    else
    {
        std::cout << "file fail to open path file" << std::endl;
        return 1;
    }

    std::string str;
    std::getline(file, str);
    cost = std::stod(str);

    int coordinate_x = 0, coordinate_y = 0;

    while(!file.eof())
    {
        std::string recv;
        std::getline(file, recv);
        if (recv == "")
            break;
        coordinate_x = std::stoi(recv.substr((recv.find('(') + 1), (recv.find(',') - 1)));
        coordinate_y = std::stoi(recv.substr(recv.find(',') + 1, (recv.find(')') - recv.find(',') - 1)));

        QGraphicsRectItem * rect = new QGraphicsRectItem();

        rect->setRect((coordinate_y) * 10, (coordinate_x) * 10, 10, 10);
        rect->setBrush(Qt::yellow);

        scene->addItem(rect);
    }
    file.close();
    return 0;
}

void map::randomSelectStartAndGoal()
{  
    srand(unsigned(time(NULL)));
    double rnd_0 ;
    double rnd_1 ;
    rnd_0 = random(30);
    rnd_1 = random(26);
    for (int i = 0 ; i < 10 ; i++)
    {
        int direct_h, direct_v;
        int r = 0, c = 0;

        double mark = rnd1(&rnd_0);
        if (mark >= 0.5)
            direct_h = 1;	//right
        else
            direct_h = 0;	//left

        mark = rnd1(&rnd_1);

        if (mark >= 0.5)
            direct_v = 4;	//bottom
        else
            direct_v = 2;	//top

        std::pair<int,int> p1;
        std::pair<int,int> p2;

        switch (direct_h + direct_v)
        {
        //left top
        case 2:
            r = (rnd1(&rnd_0) * 100) * 19 / 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100;
            p1 = std::make_pair(r,c);
            start.push_back(p1);

            r = (rnd1(&rnd_0) * 100) * 19 / 100 + 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100 + 140;
            p2 = std::make_pair(r,c);
            goal.push_back(p2);
            break;
            //right top
        case 3:
            r = (rnd1(&rnd_0) * 100) * 19 / 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100 + 140;
            p1 = std::make_pair(r,c);
            start.push_back(p1);
            r = (rnd1(&rnd_0) * 100) * 19 / 100 + 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100;
            p2 = std::make_pair(r,c);
            goal.push_back(p2);
            break;
            //left bottom
        case 4:

            r = (rnd1(&rnd_0) * 100) * 19 / 100 + 100;

            c = (rnd1(&rnd_0) * 100) * 19 / 100;
            p1 = std::make_pair(r,c);
            start.push_back(p1);

            r = (rnd1(&rnd_0) * 100) * 19 / 100;

            c = (rnd1(&rnd_0) * 100) * 19 / 100 + 140;
            p2 = std::make_pair(r,c);
            goal.push_back(p2);
            break;
            //right bottom
        case 5:

            r = (rnd1(&rnd_0) * 100) * 19 / 100 + 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100 + 140;
            p1 = std::make_pair(r,c);
            start.push_back(p1);

            r = (rnd1(&rnd_0) * 100) * 19 / 100;
            c = (rnd1(&rnd_0) * 100) * 19 / 100;
            p2 = std::make_pair(r,c);
            goal.push_back(p2);
            break;
        }
    }
}
