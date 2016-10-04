#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "node.h"
#include "weightedastar.h"
#include "pathdisplay.h"
#include "doastar.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QTime>
#include <string>
#include <fstream>
#include <iostream>
#include<vector>
#define BOARDER_WIDTH 1600
#define BOARDER_HEIGHT 1200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_Create_Map_clicked()
{
    ui->label->show();
    ui->label->setText("Creating...");
    ui->label->repaint();
    map *m = new map();
    m->mapCreator();
    ui->label->setText("Map created. Now writing to the file...");
    ui->label->repaint();
    std::string map_name = ui->le_map_name->text().toStdString();
    m->mapWriter(map_name);
    ui->label->setText("Done!");
    ui->label->repaint();
    delete m;
}

void MainWindow::on_bt_Load_and_print_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string map_name = ui->le_print_map_name->text().toStdString();
    if (map_name == "")
        map_name = "map.txt";
    map *m = new map();
    int ret = m->mapLoader(map_name, scene);
    if (ret == 0)
    {
        QGraphicsView * view = new QGraphicsView(scene);

        view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //this->setCentralWidget(view);
        view->show();
    }
    else if (ret == 1)
    {
        ui->label->setText("Map File Not Found!");
        ui->label->repaint();
    }
    delete m;
}

void MainWindow::on_bt_run_weighted_A_star_clicked()
{
    double weight;
    if (ui->le_weight->text() == "")
        weight = 1;
    else
    {
        std::string recv = ui->le_weight->text().toStdString();
        weight = std::stod(recv);
    }

    std::string p_map = ui->le_print_map_name->text().toStdString();
    std::string p_path = p_map.substr(0, p_map.find("."));
    p_path += "_path_";
    p_path += ui->le_weight->text().toStdString();
    p_path += ".txt";
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    weightedAStar *ds = new weightedAStar();
    std::cout<<"123";
    ds->readMap(p_map);
    QTime time;
    time.start();
   // std::cout<<"123";
    ds->findPath(weight, p_path);
    float timeCost = time.elapsed();

    map *m = new map();
    double cost;
    int ret = m->mapAndPathLoader(p_map, p_path, scene, cost);
    std::string titleString = "cost:";
    titleString += std::to_string(cost);
    titleString += "  ";
    titleString += "time:";
    titleString += std::to_string(timeCost);
    titleString += "ms";

    if (ret == 1)
    {
        ui->label->setText("Path file not found.");
        ui->label->update();
    }
    else if (ret == 0)
    {

        QGraphicsView * view = new QGraphicsView(scene);
        view->setWindowTitle(QString::fromStdString(titleString));
        view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->show();
        ui->label->setText("Path Found");
        ui->label->repaint();
        //QMouseEvent::pos();
    }

    PathDisplay *pd = new PathDisplay();
    pd->show();
    //this->setCentralWidget(view);
    delete m;
    delete ds;
}

void MainWindow::on_bt_get_report_clicked()
{

    std::vector<int> timesum(5,0);
    std::vector<int> nodessum(5,0);
    std::vector<int> closedsum(5,0);
    std::vector<int> pathlength(5,0);
    std::vector<int> avaliable(5,0);

    std::ofstream out;
    std::string report_path = ui->le_map_name_2->text().toStdString();
    report_path += "_report.txt";
//std::cout<<"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"<<std::endl;
    out.open(report_path);
    if (out.is_open())
    {

        for (int i = 0 ; i < 10 ; i++)
        {
            std::string p = ui->le_map_name_2->text().toStdString();
            p += "_";
            p += std::to_string(i);
            p += ".txt";
            double weight[5] = {0, 1, 0.5, 1.25, 2};
            std::string type[5] = {"Uniform", "A*     ","w=0.5  ","w=1.25 ","w=2    "};
            for (int j = 0 ; j < 5 ; j++)
            {
                weightedAStar *ds = new weightedAStar();
                double cost = 0;
                ds->readMap(p);
                QTime time;
                time.start();
                int nodesnum=0;
                int closednum=0;
                ds->findPath(weight[j], cost,nodesnum,closednum);
                float timeCost = time.elapsed();
                out << "-----------------------------------------------------------------" << std::endl;
                out << "File Name: " << p << std:: endl;
                out << type[j] << " | " << "cost: " << cost << " | " << "time: " << timeCost << std::endl;
                if(cost!=0){
                    timesum[j]+=timeCost;
                    pathlength[j]+=cost;
                    avaliable[j]++;
                    nodessum[j]+=nodesnum;
                   closedsum[j]+= closednum;

                }

                delete ds;
            }
            out << "-----------------------------------------------------------------" << std::endl;

        }
    }
    for    (int i=0;i<5;i++){

       // std::cout<<i<<":"<<"time:"<<timesum[i]<<",pathlength:"<<pathlength[i]<<",nodessum:"<<nodessum[i]<<",a:"<<avaliable[i]<<std::endl;
        std::cout<<i<<":"<<"time:"<<timesum[i]/avaliable[i]<<",pathlength:"<<pathlength[i]/avaliable[i]<<",nodessum:"<<nodessum[i]/avaliable[i]<<",closedsum:"<<closedsum[i]/avaliable[i]<<std::endl;
    }
    out.close();



}
