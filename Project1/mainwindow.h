#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "node.h"
#include "pathdisplay.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bt_Create_Map_clicked();

    void on_bt_Load_and_print_clicked();

    void on_bt_run_weighted_A_star_clicked();

    void on_bt_get_report_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
