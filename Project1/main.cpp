#include "mainwindow.h"
#include <QApplication>
#define BOARDER_WIDTH 1600
#define BOARDER_HEIGHT 1200

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setFixedSize(BOARDER_WIDTH ,BOARDER_HEIGHT);
    w.show();
    return a.exec();
}
