#include "loginform.h"
#include "ui_loginform.h"
#include <EBPdb/connection.hxx>
#include <QMessageBox>

//using namespace ebp;
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    _parent = (MainWindow *)parent;
    this->ui->passwortLineEdit->setEchoMode(QLineEdit::Password);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    QSharedPointer<ebp::connection> PointerToConnection = QSharedPointer<ebp::connection>(new ebp::connection(this->ui->loginLineEdit->text(),"drk"));
    if (PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
	this->_parent->validLogin(PointerToConnection);
    }
    else
    {
	QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Es konnte keine Veerbindung zur Datenbank hergestellt werden. Überprüfen Sie bitte ihre Logindaten"));
    }
}

void LoginForm::on_passwortLineEdit_returnPressed()
{
    this->ui->pushButton->setFocus();
    this->on_pushButton_clicked();
}
