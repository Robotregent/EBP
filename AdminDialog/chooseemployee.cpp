#include "chooseemployee.h"
#include "ui_chooseemployee.h"
#include "../drkv/Mitarbeiter.hxx"
ChooseEmployee::ChooseEmployee(EmployeeTableModel *_model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseEmployee),
    model(_model)
{
    ui->setupUi(this);
    this->ui->listView->setModel(this->model);
}

ChooseEmployee::~ChooseEmployee()
{
    delete ui;
}
