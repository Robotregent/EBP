#include "admindialog.h"
#include "ui_admindialog.h"
//#include "../drkv/database.hxx"

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
    this->db = new database("drk_admin","drk","drk");
}
