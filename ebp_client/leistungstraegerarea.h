#ifndef LEISTUNGSTRAEGERAREA_H
#define LEISTUNGSTRAEGERAREA_H

#include <QWidget>
#include <QList>
#include <EBPdb/Leistungstraeger.hxx>
#include "sessioncontext.h"
#include "savecontentinterface.h"
#include <QGridLayout>

namespace Ui {
    class LeistungstraegerArea;
}

class LeistungstraegerArea : public QWidget
{
    Q_OBJECT
    const SessionContext &con;
    QList <QSharedPointer< ebp::Leistungstraeger > > bewohner_leistungstraeger;
    void initField();


public:
    explicit LeistungstraegerArea(const SessionContext &context,QWidget *parent = 0);
    ~LeistungstraegerArea();

private:
    Ui::LeistungstraegerArea *ui;
    void setBoxesInColumn();
    void setBoxesInTable(int columns);
    int entryCount;
    int col;
    QGridLayout *grid;

private slots:
    void on_pushButton_clicked();
};

#endif // LEISTUNGSTRAEGERAREA_H
