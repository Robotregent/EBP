#include "betreuung.h"
#include "ui_betreuung.h"
#include <QDebug>

Betreuung::Betreuung(const SessionContext &context, QWidget *parent) :
    QWidget(parent),
    con(context),
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

