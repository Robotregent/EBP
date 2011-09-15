#include "chooseemployee.h"
#include "ui_chooseemployee.h"
#include "../drkv/Mitarbeiter.hxx"

ChooseEmployee::ChooseEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseEmployee)
{
    ui->setupUi(this);
    this->ui->EmployeeList->addItem;
}

ChooseEmployee::~ChooseEmployee()
{
    delete ui;
}

void ChooseEmployee::on_buttonBox_accepted()
{

    this->deleteLater();
}
