#include "bewohnerprotokoll.h"
#include "ui_bewohnerprotokoll.h"
#include <QDebug>

BewohnerProtokoll::BewohnerProtokoll(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::BewohnerProtokoll)
{
    ui->setupUi(this);
    qDebug() << "Protokoll";
}

BewohnerProtokoll::~BewohnerProtokoll()
{
    delete ui;
}
