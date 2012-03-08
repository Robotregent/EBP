#include "chooseemployee.h"
#include "ui_chooseemployee.h"
#include <QDebug>
#include <EBPdb/Mitarbeiter.hxx>
#include <QMessageBox>
using namespace ebp;

ChooseEmployee::ChooseEmployee(EmployeeTableModel *_model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseEmployee),
    model(_model)
{
    ui->setupUi(this);
    this->parent_ = (AdminDialog *)parent;
    this->ui->listView->setModel(this->model);
    this->ui->listView->horizontalHeader()->setStretchLastSection(true);
    this->ui->listView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ChooseEmployee::~ChooseEmployee()
{
    delete ui;
}

void ChooseEmployee::on_ButtonAbort_clicked()
{
    this->close();
}

/**
  *\brief Mitarbeiter löschen
  */
void ChooseEmployee::on_ButtonErase_clicked()
{
    EmployeeTableModel *tmp = ( EmployeeTableModel *)this->ui->listView->model();

    QSharedPointer<ebp::Mitarbeiter> ma = tmp->getMitarbeiter(this->ui->listView->currentIndex().row());

    if (!ma.isNull())
    {
	if (ma->remove(this->parent_->dbPointer()))
	{
	    QMessageBox::information(this,"Erfolg",ma->name()+" erfolgreich gelöscht");
	}
	else
	{
	    QMessageBox::critical(this,"Fehlschlag",ma->name()+" konnte nicht gelöscht werden.");
	}
    }
    this->close();
}
