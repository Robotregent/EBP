#include "decreescrollarea.h"
#include "ui_decreescrollarea.h"
#include <QDebug>

DecreeScrollArea::DecreeScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::DecreeScrollArea)
{
    ui->setupUi(this);
    qDebug() << "Verfügung";
}

DecreeScrollArea::~DecreeScrollArea()
{
    delete ui;
}
