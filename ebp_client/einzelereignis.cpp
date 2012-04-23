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
TextTransferInformation EinzelEreignis::getSelectedText()
{
    TextTransferInformation result;
    result.isEmpty = true;
    if(this->ui->textBrowser->textCursor().hasSelection())
    {
        result.information="\n"+ QDateTime::currentDateTime().toString("ddd MMMM d yy")+tr(" Texttransfer aus Gruppenbuch, Eintrag vom ")+this->ui->datumDateTimeEdit->dateTime().toString()+":";
	result.textTransferFragment = this->ui->textBrowser->textCursor().selection();
	result.isEmpty=false;
    }
    return result;
}
QDateTime EinzelEreignis::getDatum()
{
    return this->ui->datumDateTimeEdit->dateTime();
}
