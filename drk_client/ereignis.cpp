#include "ereignis.h"
#include "ui_ereignis.h"
#include "newereignisdialog.h"
#include <QDebug>

Ereignis::Ereignis(TextTransferAgent *agent,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ereignis),
    transferAgent(agent)
{
    ui->setupUi(this);
    QWidget *puffer = new QWidget(this);
    pufferLayout = new QVBoxLayout();
    puffer->setLayout(pufferLayout);
    this->ui->scrollArea->setWidget(puffer);
}

Ereignis::~Ereignis()
{
    delete ui;
    delete pufferLayout;
}

void Ereignis::on_pushButton_clicked()
{
    //Dialog öffnen

    EreignisInformation info;
    info.isEmpty = true;
    NewEreignisDialog ereignisDialog(&info,this);



    if(ereignisDialog.exec()==1)
    {
	if(!info.isEmpty)
	{
	    EinzelEreignis *tmp=new EinzelEreignis(this);
	    tmp->setContent(info.time,info.MitarbeiterZeichen,info.EreignisText);

	    //Neue Eingabe anzeigen
	    this->EreignisListe.prepend(tmp);
	    this->pufferLayout->insertWidget(0,tmp);

	    //TextransferInterface registrieren
	    this->transferAgent->registerNewInterface(tmp);
	}
    }

}
