#include "newereignisdialog.h"
#include "ui_newereignisdialog.h"
#include <QDate>

NewEreignisDialog::NewEreignisDialog(EreignisInformation *_ereignis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEreignisDialog),
    ereignis(_ereignis)

{
    ui->setupUi(this);
    this->setModal(true);
    QDate today;
    this->ui->dateTimeEdit->setDate(today.currentDate());
}

NewEreignisDialog::~NewEreignisDialog()
{
    delete ui;
}

void NewEreignisDialog::on_buttonBox_accepted()
{
    ereignis->time = this->ui->dateTimeEdit->dateTime();
    ereignis->EreignisText = this->ui->EreignisText->toHtml();
    ereignis->isEmpty = false;
}
