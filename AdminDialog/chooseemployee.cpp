#include "chooseemployee.h"
#include "ui_chooseemployee.h"

ChooseEmployee::ChooseEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseEmployee)
{
    ui->setupUi(this);
}

ChooseEmployee::~ChooseEmployee()
{
    delete ui;
}
