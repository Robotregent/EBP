#include "infoframe.h"
#include "ui_infoframe.h"
#include <exception>
#include <QDebug>

InfoFrame::InfoFrame(ChooseBwDialog *_bewohner, ChooseWgDialog *_wohngruppe,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InfoFrame),
    bewohner(_bewohner),
    wohngruppe(_wohngruppe)
{
    ui->setupUi(this);
}

InfoFrame::~InfoFrame()
{
    delete ui;
}
void InfoFrame::setCurBewohner(QString Bew)
{
    this->ui->BewohnerLabel->setText(  Bew);
}
void InfoFrame::setCurWohngruppe(QString group)
{
    this->ui->WohngruppenLabel->setText( group);
}

void InfoFrame::on_pushButton_clicked()
{
    try
    {
        this->bewohner->show();
    }
    catch(std::exception &ex )
    {
        qDebug()<< "Exception";
    }
}

void InfoFrame::on_pushButton_2_clicked()
{
    try
    {
	this->wohngruppe->show();
    }
    catch(std::exception &ex )
    {
        qDebug()<< "Exception";
    }
}
