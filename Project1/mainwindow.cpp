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
    ds->readMap(p_map);
    QTime time;
    time.start();
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
