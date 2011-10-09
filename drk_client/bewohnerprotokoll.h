#ifndef BEWOHNERPROTOKOLL_H
#define BEWOHNERPROTOKOLL_H

#include <QScrollArea>

namespace Ui {
    class BewohnerProtokoll;
}

class BewohnerProtokoll : public QScrollArea
{
    Q_OBJECT

public:
    explicit BewohnerProtokoll(QWidget *parent = 0);
    ~BewohnerProtokoll();

private:
    Ui::BewohnerProtokoll *ui;
};

#endif // BEWOHNERPROTOKOLL_H
