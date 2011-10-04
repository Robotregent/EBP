#include "infoframe.h"
#include "ui_infoframe.h"

InfoFrame::InfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InfoFrame)
{
    ui->setupUi(this);
}

InfoFrame::~InfoFrame()
{
    delete ui;
}
