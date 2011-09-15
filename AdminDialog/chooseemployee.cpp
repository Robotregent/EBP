#include "chooseemployee.h"
#include "ui_chooseemployee.h"
#include "../drkv/Mitarbeiter.hxx"
ChooseEmployee::ChooseEmployee(EmployeeTableModel *_model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseEmployee),
    model(_model)
{
    ui->setupUi(this);
    this->parent_ = (AdminDialog *)parent;
    this->ui->listView->setModel(this->model);
    this->ui->listView->horizontalHeader()->setStretchLastSection(true);

}

ChooseEmployee::~ChooseEmployee()
{
    delete ui;
}

void ChooseEmployee::on_ButtonAbort_clicked()
{
    this->close();
}

void ChooseEmployee::on_ButtonErase_clicked()
{
    EmployeeTableModel *tmp = ( EmployeeTableModel *)this->ui->listView->model();
    QList < QLazyWeakPointer < Wohngruppe> > w;
    QList < QLazyWeakPointer < Projekt> > p ;
    QList < QLazyWeakPointer < Bewohner> > b ;

    int row = this->ui->listView->currentIndex().row();

    Mitarbeiter ma(tmp->login(row),Mitarbeiter::WohnheimRecht,tmp->name(row)," "," " ,w,p,b);

    ma.remove(this->parent_->dbPointer());
    this->close();
}
