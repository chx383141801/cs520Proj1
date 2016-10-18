#include "pathdisplay.h"
#include "ui_pathdisplay.h"
#include "mainwindow.h"
#include <string>
#include <fstream>

PathDisplay::PathDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathDisplay)
{
    ui->setupUi(this);
}

PathDisplay::~PathDisplay()
{
    delete ui;
}

void PathDisplay::on_bt_get_info_clicked()
{
    std::string row = ui->le_row_number->text().toStdString();
    std::string column = ui->le_column_number->text().toStdString();
    std::string coordinate = "(";
    coordinate += row;
    coordinate += ",";
    coordinate += column;
    coordinate += ")";

    std::ifstream in;
    std::string file_path = ui->le_map_name->text().toStdString();
    std::string weight = ui->le_weight->text().toStdString();
    std::string p_path = file_path.substr(0, file_path.find("."));
    p_path += "_path_";
    p_path += weight;
    p_path += "_info.txt";
    in.open(p_path);
    if (in.is_open())
    {
        int signal = 0;
        std::string recv;
        while (std::getline(in, recv))
        {
            if(recv.find(coordinate) != -1)
            {
                std::string gn_hn = recv.substr(recv.find(" ")+1);
                std::string gn = gn_hn.substr(0, gn_hn.find(","));
                std::string hn = gn_hn.substr(gn_hn.find(",")+1);
                std::string Qgn = "GN-> ";
                Qgn += gn;
                ui->label_GN->setText(QString::fromStdString(Qgn));
                ui->label_GN->repaint();
                std::string Qhn = "HN-> ";
                Qhn += hn;
                ui->label_HN->setText(QString::fromStdString(Qhn));
                ui->label_HN->repaint();
                float f_gn = std::stof(gn);
                float f_hn = std::stof(hn);
                float f_fn = f_gn + f_hn;
                std::string fn = std::to_string(f_fn);
                std::string Qfn = "FN-> ";
                Qfn += fn;
                ui->label_FN->setText(QString::fromStdString(Qfn));
                ui->label_FN->repaint();
                signal = 1;
                break;
            }
        }
        if (signal == 0)
        {
            ui->label_HN->setText("HN-> NULL");
            ui->label_HN->repaint();
            ui->label_FN->setText("FN-> NULL");
            ui->label_FN->repaint();
            ui->label_GN->setText("GN-> NULL");
            ui->label_GN->repaint();
        }
    }
    in.close();

}

