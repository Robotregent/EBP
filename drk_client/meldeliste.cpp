#include "meldeliste.h"
#include "ui_meldeliste.h"

MeldeListe::MeldeListe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeldeListe)
{
    ui->setupUi(this);
    QDate today;
    this->ui->curDay->setDate(today.currentDate());
    this->ui->from->setDate(today.currentDate());
    this->ui->to->setDate(today.currentDate());
}

MeldeListe::~MeldeListe()
{
    delete ui;
}
