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

private slots:
    void on_addTeilnehmer_clicked();

private:
    Ui::BewohnerProtokoll *ui;
};

#endif // BEWOHNERPROTOKOLL_H
