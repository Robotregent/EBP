#include "datumdialog.h"
#include "ui_datumdialog.h"

DatumDialog::DatumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatumDialog)
{
    ui->setupUi(this);
}

DatumDialog::~DatumDialog()
{
    delete ui;
}
