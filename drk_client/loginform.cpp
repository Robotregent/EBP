#include "loginform.h"
#include "ui_loginform.h"
#include "../drkv/connection.hxx"
#include <QMessageBox>

using namespace drkv;
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    _parent = (MainWindow *)parent;
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    QSharedPointer<connection> PointerToConnection = QSharedPointer<connection>(new connection(this->ui->loginLineEdit->text(),"drk"));
    if (PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
	this->_parent->validLogin(PointerToConnection);
    }
    else
    {
	QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Es konnte keine Veerbindung zur Datenbank hergestellt werden. Überprüfen Sie bitte ihre Logindaten"));
    }
}
