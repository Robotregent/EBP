#include "dokumentation.h"
#include "ui_dokumentation.h"

Dokumentation::Dokumentation(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dokumentation)
{
    ui->setupUi(this);
    this->ui->Name->setText(name);
}

Dokumentation::~Dokumentation()
{
    delete ui;
}
