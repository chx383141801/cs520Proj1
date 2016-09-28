#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "node.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <string>

#define BOARDER_WIDTH 1600
#define BOARDER_HEIGHT 1200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string path = "map.txt";
    map *m = new map();
    //m->mapLoader(path, scene);
    m->maptester(scene);
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0,0,10,10);
    scene->addItem(rect);
    QGraphicsView * view = new QGraphicsView(scene);

    view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setCentralWidget(view);
    delete m;
}

MainWindow::~MainWindow()
{
    delete ui;
}
