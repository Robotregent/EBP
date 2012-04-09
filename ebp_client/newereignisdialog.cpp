#include "newereignisdialog.h"
#include "ui_newereignisdialog.h"

NewEreignisDialog::NewEreignisDialog(EreignisInformation *_ereignis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEreignisDialog),
    ereignis(_ereignis)

{
    ui->setupUi(this);
    this->setModal(true);
}

NewEreignisDialog::~NewEreignisDialog()
{
    delete ui;
}

void NewEreignisDialog::on_buttonBox_accepted()
{
    ereignis->time = this->ui->dateTimeEdit->dateTime();
    ereignis->EreignisText = this->ui->EreignisText->toHtml();
    //ereignis->MitarbeiterZeichen = this->ui->MAZeichen->text();
    ereignis->isEmpty = false;
}
