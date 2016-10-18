#ifndef PATHDISPLAY_H
#define PATHDISPLAY_H

#include <QWidget>
#include <QString>
#include <string>

namespace Ui {
class PathDisplay;
}

class PathDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PathDisplay(QWidget *parent = 0);
    ~PathDisplay();

private slots:
    void on_bt_get_info_clicked();

private:
    Ui::PathDisplay *ui;
};

#endif // PATHDISPLAY_H
