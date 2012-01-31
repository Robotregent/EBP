#include "gruppenbuch.h"
#include "ui_gruppenbuch.h"

Gruppenbuch::Gruppenbuch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gruppenbuch)
{
    ui->setupUi(this);
}

Gruppenbuch::~Gruppenbuch()
{
    delete ui;
}
