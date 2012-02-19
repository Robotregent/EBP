#include "dokumentation.h"
#include "ui_dokumentation.h"

Dokumentation::Dokumentation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dokumentation)
{
    ui->setupUi(this);
}

Dokumentation::~Dokumentation()
{
    delete ui;
}
