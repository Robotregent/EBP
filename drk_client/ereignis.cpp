#include "ereignis.h"
#include "ui_ereignis.h"
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
    //Widget für neue Eingabe erzeugen und befüllen
    EinzelEreignis *tmp=new EinzelEreignis(this);
    tmp->setContent(QDateTime::currentDateTime(),this->ui->MAZeichen->text(),this->ui->EreignisText->toHtml() );

    //Neue Eingabe anzeigen
    this->EreignisListe.prepend(tmp);
    this->pufferLayout->insertWidget(0,tmp);

    //Eingabefeld löschen
    this->ui->MAZeichen->clear();
    this->ui->EreignisText->clear();

    //TextransferInterface registrieren
    this->transferAgent->registerNewInterface(tmp);

}
