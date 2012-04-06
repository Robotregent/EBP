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
void InfoFrame::setCurBewohner(QString Bew)
{
    this->ui->BewohnerLabel->setText(  "Aktueller Bewohner:	"+Bew);
    //this->_curBewohner=Bew
}
void InfoFrame::setCurWohngruppe(QString group)
{
    this->ui->WohngruppenLabel->setText( "Aktuelle Wohngruppe:	    "+ group);
}
