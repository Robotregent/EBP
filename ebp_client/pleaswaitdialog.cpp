#include "pleaswaitdialog.h"
#include "ui_pleaswaitdialog.h"

PleasWaitDialog::PleasWaitDialog(MainWindow *mw , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PleasWaitDialog)
{
    ui->setupUi(this);
    this->_mw=mw;
}

PleasWaitDialog::~PleasWaitDialog()
{
    delete ui;
}


void PleasWaitDialog::on_pushButton_clicked()
{
    this->_mw->close();
    this->close();
}
