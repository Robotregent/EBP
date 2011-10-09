#include "betreuung.h"
#include "ui_betreuung.h"
#include <QDebug>

Betreuung::Betreuung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Betreuung)
{
    ui->setupUi(this);
    //this->ui->mitarbeiternrLabel->resize(this->ui->aufentahltsbestimmungLabel->size());
    qDebug() << this->ui->aufentahltsbestimmungLabel->width();
    qDebug() <<this->ui->mitarbeiternrLabel->width();
}

Betreuung::~Betreuung()
{
    delete ui;
}
