#include "loginform.h"
#include "ui_loginform.h"
#include <EBPdb/connection.hxx>
#include <QMessageBox>
#include <QSettings>

//using namespace ebp;
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);;
    this->ui->passwortLineEdit->setEchoMode(QLineEdit::Password);
    QSettings settings("EBP.ini", QSettings::IniFormat);
    this->dbName = settings.value("db",QVariant("ebp")).toString();
    this->dbHost = settings.value("host",QVariant("localhost")).toString();
    this->dbPort = settings.value("port",QVariant(3306)).toUInt();
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    QSharedPointer<ebp::connection> PointerToConnection = QSharedPointer<ebp::connection>(new ebp::connection(this->ui->loginLineEdit->text(),this->dbName,this->dbHost,this->dbPort));
    if (PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
	QSharedPointer<ebp::Mitarbeiter> curMa = PointerToConnection->mitarbeiter();
	if (curMa.isNull())
	    QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Der Login stimmt mit keinem Mitarbeiter in der Datenbank überein. Bitte wenden Sie sich an Ihren Administrator."));
	else
	{
	    emit validLogin(curMa,PointerToConnection);
	}
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
