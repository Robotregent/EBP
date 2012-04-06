#ifndef BEWOHNERPROTOKOLL_H
#define BEWOHNERPROTOKOLL_H

#include <QScrollArea>
#include "texttransferinterface.h"
namespace Ui {
    class BewohnerProtokoll;
}

class BewohnerProtokoll : public QScrollArea, public TextTransferInterface
{
    Q_OBJECT

public:
    explicit BewohnerProtokoll(QWidget *parent = 0);
    TextTransferInformation getSelectedText();
    ~BewohnerProtokoll();

private slots:
    void on_addTeilnehmer_clicked();

private:
    Ui::BewohnerProtokoll *ui;
};

#endif // BEWOHNERPROTOKOLL_H
