#include "ereignis.h"
#include "ui_ereignis.h"

Ereignis::Ereignis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ereignis)
{
    ui->setupUi(this);
}

Ereignis::~Ereignis()
{
    delete ui;
}
