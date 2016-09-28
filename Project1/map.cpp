#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#define random(x)(rand()%x)

map::map()
{
    array = new node[120][160];
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0 ; j < 160 ; j++)
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
        int ret = randomSelectHighway(array, 120, 160);
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
                array[i][j].weight = 'a';
            else if (array[i][j].isHighway == 'b')
                array[i][j].weight = 'b';
        }
    }

    //select blocked cells
    randomSelectBlock(array, 120, 160);
    randomSelectStartAndGoal();

    return 0;
}

int map::randomSelectHighway(node array[120][160], int row, int column)
{
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
                if (array[r][c].isHighway == 'n')
                {
                    vect.push_back(&array[r][c]);
                    if (direction == 1)
                        r++;
                    else
                        r--;
                }
                else
                {
                    vect.clear();
                    isSuccess = 1;
                    break;
                }
            }
        }
        else
        {
            for (int j = 0; j < 20 && c < column && c >= 0; j++)
            {
                if (array[r][c].isHighway == 'n')
                {
                    vect.push_back(&array[r][c]);
                    if (direction == 1)
                        c++;
                    else
                        c--;
                }
                else
                {
                    vect.clear();
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

    if (vect.size() < 100)
    {
        isSuccess = 1;
        vect.clear();
        return isSuccess;
    }

    for (it = vect.begin(); it != vect.end(); it++)
    {
        node * n = *it;
        if (n->weight == '1')
            n->isHighway = 'a';
        else if (n->weight == '2')
            n->isHighway = 'b';
        else
            std::cout << "Exception on marking highway!" << std::endl;
    }

    return isSuccess;
}

void map::randomSelectHard(node array[][160], int row, int column, int amount)
{
    double rnd_0 = 5.0;
    double rnd_1 = 6.0;
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

        for (int j = r - 15; j < r + 31; j++)
        {
            for (int k = c - 15; k < c + 31; k++)
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
    double mark = rnd1(&rnd_0);
    int amount = row * column * 0.2;
    int r, c;

    for (int i = 0; i < amount;)
    {
        r = (rnd1(&rnd_0) * 100) * 120 / 100;
        c = (rnd1(&rnd_1) * 100) * 160 / 100;
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

std::vector<std::string> split(const  std::string& s, const std::string& delim)
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
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

void map::mapWriter()
{
    std::ofstream file;
    file.open("map.txt");
    std::vector <int>::iterator it;
    for (it = start.begin(); it != start.end(); it++)
        file << *it << ' ';
    file << std::endl;
    for (it = goal.begin(); it != goal.end(); it++)
        file << *it << ' ';
    file << std::endl;
    int counter = 0;
    for (it = hdCenter.begin(); it != hdCenter.end(); it++)
    {
        file << *it << ' ';
        ++counter;
        if (counter % 2 == 0)
            file << std::endl;
    }

    counter = 0;
    for (int i = 0 ; i < 120 ; i++)
    {
        for (int j = 0; j < 160; j++)
        {
            file << array[i][j].weight;
            counter++;
            if (counter % 160 == 0)
                file << std::endl;
        }
    }
    file.close();
}

void map::mapLoader(std::string path, QGraphicsScene *scene)
{
    std::ifstream file;
    file.open("D:\\Users\\Documents\\Project1\\map.txt");
    if (file.is_open())
        std::cout << "file is open" << std::endl;
    else
        std::cout << "file fail to open" << std::endl;

    QGraphicsRectItem * rect = new QGraphicsRectItem();

    std::vector <std::string> strVect;

    for (int i = 0 ; i < 10 ; i++)
    {
        std::string str;
        std::getline(file, str);

        strVect.push_back(str);
    }

    for (int i = 0 ; i < 120 ; i++)
    {
        std::string str(160,'0');
        std::getline(file, str);
        for (int j = 0 ; j < 160 ; j++)
        {
            if (str[j] == '0')
            {
                rect->setRect(i*10,j*10,10,10);
                rect->setBrush(Qt::black);
            }
            else if (str[j] == '1')
            {
                rect->setRect(i*10,j*10,10,10);
                rect->setBrush(Qt::white);
            }
            else if (str[j] == '2')
            {
                rect->setRect(i*10,j*10,10,10);
                rect->setBrush(Qt::gray);
            }
            else if (str[j] == 'a')
            {
                rect->setRect(i*10,j*10,10,10);
                rect->setBrush(Qt::blue);
            }
            else if (str[j] == 'b')
            {
                rect->setRect(i*10,j*10,10,10);
                rect->setBrush((Qt::darkBlue));
            }
            scene->addItem(rect);
        }
    }
}

void map::maptester(QGraphicsScene *scene)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(10,10,10,10);
    scene->addItem(rect);
}

void map::randomSelectStartAndGoal()
{
    int direct_h, direct_v;
    int r = 0, c = 0;

    srand(unsigned(time(NULL)));
    double rnd_0 = random(15);
    double rnd_1 = random(17);
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

    switch (direct_h + direct_v)
    {
        //left top
    case 2:
        srand(unsigned(time(NULL)));
        r = random(19);
        srand(unsigned(time(NULL)));
        c = random(19);
        start.push_back(r);
        start.push_back(c);
        srand(unsigned(time(NULL)));
        r = random(19) + 100;
        srand(unsigned(time(NULL)));
        c = random(19) + 140;
        goal.push_back(r);
        goal.push_back(c);
        break;
        //right top
    case 3:
        srand(unsigned(time(NULL)));
        r = random(19);
        srand(unsigned(time(NULL)));
        c = random(19) + 140;
        start.push_back(r);
        start.push_back(c);
        srand(unsigned(time(NULL)));
        r = random(19) + 100;
        srand(unsigned(time(NULL)));
        c = random(19);
        goal.push_back(r);
        goal.push_back(c);
        break;
        //left bottom
    case 4:
        srand(unsigned(time(NULL)));
        r = random(19) + 100;
        srand(unsigned(time(NULL)));
        c = random(19);
        start.push_back(r);
        start.push_back(c);
        srand(unsigned(time(NULL)));
        r = random(19);
        srand(unsigned(time(NULL)));
        c = random(19) + 140;
        goal.push_back(r);
        goal.push_back(c);
        break;
        //right bottom
    case 5:
        srand(unsigned(time(NULL)));
        r = random(19) + 100;
        srand(unsigned(time(NULL)));
        c = random(19) + 140;
        start.push_back(r);
        start.push_back(c);
        srand(unsigned(time(NULL)));
        r = random(19);
        srand(unsigned(time(NULL)));
        c = random(19);
        goal.push_back(r);
        goal.push_back(c);
        break;
    }

}
