#include "leistungstraegerarea.h"
#include "leistungstraegerbox.h"
#include "ui_leistungstraegerarea.h"
#include <QVBoxLayout>
#include <QGridLayout>
LeistungstraegerArea::LeistungstraegerArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeistungstraegerArea)
{
    ui->setupUi(this);
    //QVBoxLayout *vlay = new QVBoxLayout();
    QGridLayout *glay= new QGridLayout();
    LeistungstraegerBox *tmp;
    QWidget *wid = new QWidget(this);

    for (int i = 0 ; i <4; ++i)
    {
        for (int k = 0; k < 2; ++k)
        {
            tmp=new LeistungstraegerBox(this);
            //vlay->addWidget(tmp);
            tmp->setTitle(tr("Test Test"));
            glay->addWidget(tmp,i,k);
        }


    }
    //wid->setLayout(vlay);
    wid->setLayout(glay);
    this->ui->scrollArea->setWidget(wid);



}

LeistungstraegerArea::~LeistungstraegerArea()
{
    delete ui;
}
