#include "leistungstraegerbox.h"
#include "ui_leistungstraegerbox.h"

LeistungstraegerBox::LeistungstraegerBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::LeistungstraegerBox)
{
    ui->setupUi(this);
}

LeistungstraegerBox::~LeistungstraegerBox()
{
    delete ui;
}
