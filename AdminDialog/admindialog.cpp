#include "admindialog.h"
#include "ui_admindialog.h"
#include "chooseemployee.h"
#include "employeelistmodel.h"
#include "../drkv/Mitarbeiter.hxx"
//#include "../drkv/database.hxx"
#include <QList>
AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->init();
    this->PointerToDB  = QSharedPointer<database>(db);
    this->model = new EmployeeTableModel(Mitarbeiter::getAll(this->PointerToDB));

}

AdminDialog::~AdminDialog()
{
    delete ui;
}
void AdminDialog::init()
{
    this->db = new database("drk_admin","drk","drk");
}

void AdminDialog::on_button_MA_suchen_clicked()
{
    ChooseEmployee *e=new ChooseEmployee(this->model,this);
    e->setModal(true);
    e->setVisible(true);
}

void AdminDialog::on_button_MA_speichern_clicked()
{
    QList < QLazyWeakPointer < Wohngruppe> > w;
    QList < QLazyWeakPointer < Projekt> > p ;
    QList < QLazyWeakPointer < Bewohner> > b ;
    Mitarbeiter ma(this->ui->lineEdit_MA_vorname->text(),Mitarbeiter::WohnheimRecht,this->ui->lineEdit_MA_nachname->text()," "," " ,w,p,b);
    ma.create(this->PointerToDB,"blabla");
}

void AdminDialog::on_button_abbrechen_clicked()
{
    this->close();
}
