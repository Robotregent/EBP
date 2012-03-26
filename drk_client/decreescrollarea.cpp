#include "decreescrollarea.h"
#include "ui_decreescrollarea.h"
#include <QDebug>

DecreeScrollArea::DecreeScrollArea(const SessionContext &context,QWidget *parent) :
    QScrollArea(parent),
    con(context),
    ui(new Ui::DecreeScrollArea)
{
    ui->setupUi(this);
    qDebug() << "Verfügung";
}

DecreeScrollArea::~DecreeScrollArea()
{
    delete ui;
}
