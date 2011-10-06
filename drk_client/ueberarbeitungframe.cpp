#include "ueberarbeitungframe.h"
#include "ui_ueberarbeitungframe.h"

UeberarbeitungFrame::UeberarbeitungFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UeberarbeitungFrame)
{
    ui->setupUi(this);
}

UeberarbeitungFrame::~UeberarbeitungFrame()
{
    delete ui;
}
