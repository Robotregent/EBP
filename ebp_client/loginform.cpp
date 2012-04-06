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
    ui->setupUi(this);
    _parent = (MainWindow *)parent;
    this->ui->passwortLineEdit->setEchoMode(QLineEdit::Password);
    QSettings settings("EBP.ini", QSettings::IniFormat);
    this->dbName = settings.value("db",QVariant("ebp")).toString();
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    QSharedPointer<ebp::connection> PointerToConnection = QSharedPointer<ebp::connection>(new ebp::connection(this->ui->loginLineEdit->text(),this->dbName));
    if (PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
	//QList < QSharedPointer<ebp::Mitarbeiter> > allMa = ebp::Mitarbeiter::loadAll(PointerToConnection);
	QSharedPointer<ebp::Mitarbeiter> curMa = PointerToConnection->mitarbeiter();
	/*curMa.isNull();
	for (int i = 0 ; i < allMa.count(); i++)
	{
	    if (this->ui->loginLineEdit->text() == allMa.at(i)->login())
		curMa = allMa.at(i);
	}*/
	if (curMa.isNull())
		QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Der Login stimmt mit keinem Mitarbeiter in der Datenbank überein. Bitte wenden Sie sich an Ihren Administrator."));
	else
	{
	    this->_parent->setCurMitarbeiter(curMa);
	    this->_parent->validLogin(PointerToConnection);
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
