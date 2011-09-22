#include "decreescrollarea.h"
#include "ui_decreescrollarea.h"

DecreeScrollArea::DecreeScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::DecreeScrollArea)
{
    ui->setupUi(this);
}

DecreeScrollArea::~DecreeScrollArea()
{
    delete ui;
}
