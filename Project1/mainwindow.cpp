#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "node.h"
#include "doastar.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QDialog>
#include <string>

#define BOARDER_WIDTH 1600
#define BOARDER_HEIGHT 1200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string path = "map.txt";
    map *m = new map();
    m->mapLoader(path, scene);

    QGraphicsView * view = new QGraphicsView(scene);

    view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setCentralWidget(view);
    delete m;
    */

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
    m->mapWriter();
    ui->label->setText("Done!");
    ui->label->repaint();
    delete m;
}

void MainWindow::on_bt_Load_and_print_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string path = "D:\\Users\\Documents\\build-Project1-Desktop_Qt_5_6_1_MSVC2015_64bit-Debug\\map.txt";
    map*m = new map();
    m->mapLoader(path, scene);

    QGraphicsView * view = new QGraphicsView(scene);

    view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setCentralWidget(view);
    view->show();
    delete m;
}



void MainWindow::on_bt_run_A_Star_clicked()
{
    std::string p_path = "D:\\Users\\Documents\\build-Project1-Desktop_Qt_5_6_1_MSVC2015_64bit-Debug\\path.txt";
    std::string p_map = "D:\\Users\\Documents\\build-Project1-Desktop_Qt_5_6_1_MSVC2015_64bit-Debug\\map.txt";
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    doastar *ds = new doastar();
    ds->readMap(p_map);
    ds->findPath();

    map *m = new map();
    m->mapAndPathLoader(p_map, p_path, scene);
    QGraphicsView * view = new QGraphicsView(scene);

    view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setCentralWidget(view);
    view->show();
    delete m;
    delete ds;
}
