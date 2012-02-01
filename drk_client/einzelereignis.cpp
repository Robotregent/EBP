#include "einzelereignis.h"
#include "ui_einzelereignis.h"

EinzelEreignis::EinzelEreignis(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EinzelEreignis)
{
    ui->setupUi(this);
}

EinzelEreignis::~EinzelEreignis()
{
    delete ui;
}
void EinzelEreignis::setContent(QDateTime datum, QString mitarbeiter, QString text)
{
    this->ui->datumDateTimeEdit->setDateTime(datum);
    this->ui->mitarbeiterLineEdit->setText(mitarbeiter);
    this->ui->textBrowser->setHtml(text);
}
