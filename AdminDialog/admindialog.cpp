#include "admindialog.h"
#include "ui_admindialog.h"
#include "chooseemployee.h"
#include "employeelistmodel.h"
#include "../drkv/Mitarbeiter.hxx"
//#include "../drkv/database.hxx"

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
