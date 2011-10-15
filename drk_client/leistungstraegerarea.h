#ifndef LEISTUNGSTRAEGERAREA_H
#define LEISTUNGSTRAEGERAREA_H

#include <QWidget>

namespace Ui {
    class LeistungstraegerArea;
}

class LeistungstraegerArea : public QWidget
{
    Q_OBJECT

public:
    explicit LeistungstraegerArea(QWidget *parent = 0);
    ~LeistungstraegerArea();

private:
    Ui::LeistungstraegerArea *ui;
};

#endif // LEISTUNGSTRAEGERAREA_H
