#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->init();

}

AdminDialog::~AdminDialog()
{
    delete ui;
}
void AdminDialog::init()
{

}
